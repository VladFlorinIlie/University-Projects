#pragma once
#include <include/glm.h>
#include <include/math.h>

	class CameraTema
	{
		public:
			CameraTema()
			{
				position = glm::vec3(0, 2, 5);
				forward = glm::vec3(0, 0, -1);
				up		= glm::vec3(0, 1, 0);
				right	= glm::vec3(1, 0, 0);
				distanceToTarget = 2;
			}

			CameraTema(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
			{
				Set(position, center, up);
			}

			~CameraTema()
			{ }

			// Update camera
			void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
			{
				this->position = position;
				forward = glm::normalize(center-position);
				right	= glm::cross(forward, up);
				this->up = glm::cross(right,forward);
			}

			void MoveForward(float distance)
			{
				glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
				this->position += dir * distance;
			}

			void TranslateForward(float distance)
			{
				this->position += glm::normalize(this->forward) * distance;
			}

			void TranslateUpword(float distance)
			{
				this->position += glm::normalize(this->up) * distance;
			}

			void MoveUpword(float distance)
			{
				this->position += glm::normalize(glm::vec3(0, 1, 0)) * distance;
			}

			void TranslateRight(float distance)
			{
				// Translate the camera using the "right" vector
				// Usually translation using camera "right' is not very useful because if the camera is rotated around the "forward" vector 
				// translation over the right direction will have an undesired effect; the camera will get closer or farther from the ground
				// Using the projected right vector (onto the ground plane) makes more sense because we will keep the same distance from the ground plane
				glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
				this->position += glm::normalize(dir) * distance;
			}

			void RotateFirstPerson_OX(float angle)
			{
				// Compute the new "forward" and "up" vectors
				// Attention! Don't forget to normalize the vectors
				// Use glm::rotate()
				glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, this->right);

				glm::vec4 newFor = rot * glm::vec4(this->forward, 1.0f);
				this->forward = glm::normalize(glm::vec3(newFor));

				this->up = glm::cross(this->right, this->forward);
			}

			void RotateFirstPerson_OY(float angle)
			{
				// Compute the new "forward", "up" and "right" vectors
				// Don't forget to normalize the vectors
				// Use glm::rotate()
				glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));

				glm::vec4 newFor = rot * glm::vec4(this->forward, 1.0f);
				this->forward = glm::normalize(glm::vec3(newFor));

				glm::vec3 newRight = rot * glm::vec4(this->right, 1.0f);
				this->right = glm::normalize(glm::vec3(newRight));

				this->up = glm::cross(this->right, this->forward);
			}

			void RotateFirstPerson_OZ(float angle)
			{
				// Compute the new Right and Up, Forward stays the same
				// Don't forget to normalize the vectors
				glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, this->forward);

				glm::vec3 newRight = rot * glm::vec4(this->right, 1.0f);
				this->right = glm::normalize(glm::vec3(newRight));

				this->up = glm::cross(this->right, this->forward);
			}

			void RotateThirdPerson_OX(float angle)
			{
				// Rotate the camera in Third Person mode - OX axis
				// Use distanceToTarget as translation distance
				this->MoveForward(this->distanceToTarget);
				this->RotateFirstPerson_OX(angle);
				this->MoveForward(-this->distanceToTarget);
			}

			void RotateThirdPerson_OY(float angle)
			{
				// Rotate the camera in Third Person mode - OY axis
				this->MoveForward(this->distanceToTarget);
				this->RotateFirstPerson_OY(angle);
				this->MoveForward(-this->distanceToTarget);
			}

			void RotateThirdPerson_OZ(float angle)
			{
				// Rotate the camera in Third Person mode - OZ axis
				this->MoveForward(this->distanceToTarget);
				this->RotateFirstPerson_OZ(angle);
				this->MoveForward(this->distanceToTarget);
			}

			glm::mat4 GetViewMatrix()
			{
				// Returns the View Matrix
				return glm::lookAt(position, position + forward, up);
			}

			glm::vec3 GetTargetPosition()
			{
				return position + forward * distanceToTarget;
			}

		public:
			float distanceToTarget;
			glm::vec3 position;
			glm::vec3 forward;
			glm::vec3 right;
			glm::vec3 up;
		};