#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "util.h"

// creaza socket-ul udp
int init_conn(struct sockaddr_in *addr, char *ip, int re) {
	int sockudp = -1;
	
	if (re == 1) { // verifica daca socketul a fost deja creat
		inet_aton(ip, &(addr->sin_addr)); // schimba ip-ul serverului
		return sockudp;
	}
	
	memset(addr, 0, sizeof(struct sockaddr_in));
	sockudp = socket(AF_INET, SOCK_DGRAM, 0); // creaza socket
	if (sockudp < 0) {
		return -1;
	}
	
	struct timeval tv; // timeout 3 secunde
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	if (setsockopt(sockudp, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
		return -1;
	
	addr->sin_family = AF_INET;
    addr->sin_port = htons(53);
    inet_aton(ip, &(addr->sin_addr));
	
	return sockudp;
}

// creaza mesajul catre server
unsigned char *create_msg(char *nume, char *q, int *query_size)
{
	unsigned char *tosend = malloc(512 * sizeof(unsigned char));
	char name[512];
	char arpa[14] = {0x07, 'i', 'n', '-', 'a', 'd', 'd', 'r',
					0x04, 'a', 'r', 'p', 'a', 0x00};
	int sz = 0; // dimensiunea mesajului
	dns_header_t header;
	dns_question_t question;
	
	memset(&header, 0, sizeof(dns_header_t));
	memset(&question, 0, sizeof(dns_question_t));
	strcpy(name, nume); // face o copie a numelui de domeniu/ip-ului
	
	header.id = htons(1); // cererea are id-ul 1
	header.rd = 1; // recursivitate
	header.qdcount = htons(1); // o singura intrebare
	
	// seteaza tipul intrebarii
	if (strcmp(q, "A") == 0)
		question.qtype = htons(A);
	else if (strcmp(q, "MX") == 0)
		question.qtype = htons(MX);
	else if (strcmp(q, "NS") == 0)
		question.qtype = htons(NS);
	else if (strcmp(q, "CNAME") == 0)
		question.qtype = htons(CNAME);
	else if (strcmp(q, "SOA") == 0)
		question.qtype = htons(SOA);
	else if (strcmp(q, "TXT") == 0)
		question.qtype = htons(TXT);
	else if (strcmp(q, "PTR") == 0)
		question.qtype = htons(PTR);
	
	question.qclass = htons(1); // clasa
	memcpy(tosend, &header, sizeof(dns_header_t)); // copiaza continutul
	sz += sizeof(dns_header_t); // in to send si actualizeaza marimea
	
	if (strcmp(q, "PTR") != 0) { // daca am primit un nume de domeniu
		char *pch;
		pch = strtok(name, ".\r\n"); // imparte numele
		while (pch != NULL) {
			tosend[sz] = strlen(pch); // pune lungimea
			sz++;
			memcpy(tosend + sz, pch, strlen(pch)); // pune caracterele
			sz += strlen(pch);
			pch = strtok(NULL, ".\r\n");
		}
		tosend[sz] = 0; // terminatorul de sir
		sz++;
	} else { // daca am primit un ip
		char *pch;
		int len = strlen(name) + 1; // lungimea
		len += sz;
		
		pch = strtok(name, ".\r\n");
		while (pch != NULL) { // pune grupurile de numere in ordine inversa
			memcpy(tosend + len - strlen(pch), pch, strlen(pch));
			len -= strlen(pch);
			len--;
			tosend[len] = strlen(pch); // pune lungimea fiecarui grup
			pch = strtok(NULL, ".\r\n");
		}
		
		sz += strlen(nume) + 1;
		memcpy(tosend + sz, arpa, 14); // adauga in-addr.arpa
		sz += 14;
	}
	
	//copiaza continul structurii question in mesaj
	memcpy(tosend + sz, &question, sizeof(dns_question_t));
	sz += sizeof(dns_question_t);
	
	*query_size = sz;
	
	//scrie in fisier intregul mesaj in format hexa
	FILE *msglog = fopen("message.log", "a");
	int i;
	for (i = 0; i < sz; i++)
		fprintf(msglog, "%02x ", tosend[i]);
	fprintf(msglog, "\n\n");
	fclose(msglog);
	
	return tosend;
}

// citeste un nume care e imparit in label-uri si sau pointer
int name_reader(unsigned char *recv, char *rez, int ind) {
	int i = ind, end_pointer = -1, cnt = 0, j, trigger = 0;
	
	// curata rezultatul
	memset(rez, 0, 512);
	while (1) {
		if (recv[i] == 0xc0) { // am gasit un pointer
			if (trigger == 0) { // salveaza pozitia curenta
				end_pointer = i + 2;
				trigger = 1;
			}
			i = recv[i + 1]; // sari la pozitia indicata
			i--;
		} else if (recv[i] == 0) // final
			break;
		else {
			unsigned int end = recv[i]; // dimensiunea grupului
			for (j = i + 1; j < i + 1 + end; j++, cnt++)
				rez[cnt] = recv[j]; // copiaza grupul in rezultat
			rez[cnt] = '.'; // adauga punct
			cnt++;
			i = j - 1; // actualizeaza pozitia
		}
		i++;
	}
	
	if (end_pointer == -1) // daca nu am gasit pointer
		return i + 1; // restul mesajului de la server va fi la i + 1
	return end_pointer; // daca am pointer, restul mesajului va fi dupa pointer
}	

// primeste msajul de la server si il intrerpreteaza
int recv_msg(int sockudp, int sz, char *name, char *q, char *srv) {
	unsigned char recv[512]; // dimensiunea maxima a unui pachet dns prin udp
	char rez[512];
	int i, tip, j, an, ns, ar;
	dns_header_t header;
	dns_rr_t response;
	
	memset(recv, 0, 512);
	recvfrom(sockudp, recv, 512, 0, NULL, NULL);
	if (recv[0] == 0 && recv[1] == 0) // adica id-ul este 0 = imposibil
		return -1; // deci serverul nu a raspuns
	
	memcpy(&header, recv, sizeof(dns_header_t));
	if (ntohs(header.rcode) != 0) // in caz de eroare
		return 0;
	
	FILE *dnslog = fopen("dns.log", "a"); // deschide dns.log
	fprintf(dnslog, "; %s - %s %s\n", srv, name, q); // scrie in fisier cererea
	
	i = sz; // sare peste header si question
	an = ntohs(header.ancount); // numarul de raspunsuri
	ns = ntohs(header.nscount);
	ar = ntohs(header.arcount);
	for (j = 0; j < an + ns + ar; j++) {
		if (j == 0 && an != 0) // inceputul fiecarei sectiuni
			fprintf(dnslog, "\n;; ANSWER SECTION:\n");
		else if (j == an && ns != 0)
			fprintf(dnslog, "\n;; AUTHORITY SECTION:\n");
		else if (j == an + ns && ar != 0)
			fprintf(dnslog, "\n;; ADDITIONAL SECTION:\n");
	
		// citeste numele de la inceputul fiecarui raspuns
		i = name_reader(recv, rez, i);
		fprintf(dnslog, "%s ", rez);
		
		// copiaza raspunsul (fara date)
		memcpy(&response, recv + i, sizeof(dns_rr_t));
		
		i += sizeof(dns_rr_t);
		tip = ntohs(response.type); // tipul raspunsului
		
		//date
		if (tip == A) { // afiseaza cei 4 octeri ai ip-ului
			fprintf(dnslog, "IN A %d.%d.%d.%d\n", recv[i], recv[i + 1],
												recv[i + 2], recv[i + 3]);
			i += 4; // avanseaza i-ul
		} else if (tip == NS) { // citeste name-ul corespunzator si avanseaza i
			i = name_reader(recv, rez, i);
			fprintf(dnslog, "IN NS %s\n", rez);
		} else if (tip == MX) {
			unsigned short pref; // citeste preference (2 octeti)
			memcpy(&pref, recv + i, 2);
			pref = ntohs(pref); // converteste pref
			i += 2;
			i = name_reader(recv, rez, i); // citeste numele
			fprintf(dnslog, "IN MX %d %s\n", pref, rez);
		} else if (tip == CNAME) { // citeste numele canonic
			i = name_reader(recv, rez, i);
			fprintf(dnslog, "IN CNAME %s\n", rez); 
		} else if (tip == TXT) {
			unsigned char txtlen = recv[i]; // lungimea textului
			int k;
			i++;
			fprintf(dnslog, "IN TXT "); 
			for (k = i; k < i + txtlen; k++) // parcurge textul si il afiseaza
				fprintf(dnslog, "%c", recv[k]);
			i = k; // pozitia curenta este dupa text
			fprintf(dnslog, "\n");
		} else if (tip == SOA) {
			i = name_reader(recv, rez, i); // primary ns
			fprintf(dnslog, "IN SOA %s ", rez);
			i = name_reader(recv, rez, i); // admin mb
			fprintf(dnslog, "%s ", rez);
			
			dns_re_soa soa; // restul datelor din raspuns
			memcpy(&soa, recv + i, sizeof(dns_re_soa)); // sunt copiate in soa
			i += sizeof(dns_re_soa);
			
			fprintf(dnslog, "%d %d %d %d %d\n", ntohl(soa.serial), 
			ntohl(soa.refr),ntohl(soa.retry), ntohl(soa.exp), ntohl(soa.min));
		} else if (tip == PTR) { // citeste numele oferit
			i = name_reader(recv, rez, i);
			fprintf(dnslog, "IN PTR %s\n", rez);
		}
	}
	fprintf(dnslog, "\n\n");
	fclose(dnslog); // inchide dns.log
	
	return 1; // am primit raspuns de la server si l-am interpretat cu succes
}

int main(int argc, char **argv)
{
	int q_size, sockudp, re = 0;
	struct sockaddr_in addr;
	FILE *in = fopen("dns_servers.conf", "r"); // deschide fiesierul cu servere
	char *srv;
	unsigned char *msg = create_msg(argv[1], argv[2], &q_size); // mesajul
	char read[1024];
	
	while (fgets(read, 1024, in) != NULL) { // citeste cate o linie
		if (read[0] == '#' || read[0] == '\r' || read[0] == '\n')
			continue; // daca linia e goala sau e comentariu => trece peste ea
		else {
			srv = strtok(read, "\r\n");
			if (re == 0) { // daca nu am creat inca socketul
				sockudp = init_conn(&addr, srv, re);
				re = 1;
			} else { // socketul este deja creat
				init_conn(&addr, srv, re);
			}
			
			// trimite mesajul catre serverul dns
			sendto(sockudp, msg, q_size, 0, (struct sockaddr*) &addr, sizeof(addr));
			// asteapta raspunsul serverului pentru a fi interpretat
			if (recv_msg(sockudp, q_size, argv[1], argv[2], srv) == 1)
				break; // daca am avut succes, ma opresc
		}
	}
	
	free(msg);
	fclose(in);

	return 0;
}