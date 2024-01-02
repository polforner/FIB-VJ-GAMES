using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlayer : MonoBehaviour
{
    public float rotationSpeed, jumpSpeed, gravity;
    public Animator playerAnimator;

    Quaternion startRotation;
    Vector3 startDirection;
    float speedY;
    bool inAir;

    // Start is called before the first frame update
    void Start()
    {
        // Store starting direction of the player with respect to the axis of the level
        startRotation = transform.rotation;
        startDirection = transform.position - transform.parent.position;
        startDirection.y = 0.0f;
        startDirection.Normalize();

        speedY = 0;
        inAir = false;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        CharacterController charControl = GetComponent<CharacterController>();
        Vector3 position;

        // Left-right movement
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D))
        {
            float angle;
            Vector3 direction, target;

            position = transform.position;
            angle = rotationSpeed * Time.deltaTime;
            direction = position - transform.parent.position;
            if (Input.GetKey(KeyCode.A))
            {
                target = transform.parent.position + Quaternion.AngleAxis(angle, Vector3.up) * direction;
                if (charControl.Move(target - position) != CollisionFlags.None)
                {
                    transform.position = position;
                    Physics.SyncTransforms();
                }
                playerAnimator.SetFloat("Rotation", -angle);
            }
            if (Input.GetKey(KeyCode.D))
            {
                target = transform.parent.position + Quaternion.AngleAxis(-angle, Vector3.up) * direction;
                if (charControl.Move(target - position) != CollisionFlags.None)
                {
                    transform.position = position;
                    Physics.SyncTransforms();
                }
                playerAnimator.SetFloat("Rotation", angle);
            }
        }
        else playerAnimator.SetFloat("Rotation", 0);

        // Correct orientation of player
        // Compute current direction
        Vector3 currentDirection = transform.position - transform.parent.position;
        currentDirection.y = 0.0f;
        currentDirection.Normalize();
        // Change orientation of player accordingly
        Quaternion orientation;
        if ((startDirection - currentDirection).magnitude < 1e-3)
            orientation = startRotation * Quaternion.AngleAxis(0.0f, Vector3.up);
        else if ((startDirection + currentDirection).magnitude < 1e-3)
            orientation = startRotation * Quaternion.AngleAxis(180.0f, Vector3.up);
        else
            orientation = startRotation * Quaternion.FromToRotation(startDirection, currentDirection);
        transform.rotation = orientation;   

        // Apply up-down movement
        position = transform.position;
        if (charControl.Move(speedY * Time.deltaTime * Vector3.up) != CollisionFlags.None)
        {
            transform.position = position;
            Physics.SyncTransforms();
        }

        if (charControl.isGrounded)
        {
            if (speedY < 0.0f)
                speedY = 0.0f;

            if (inAir) {
                playerAnimator.SetTrigger("Land");
                inAir = false;
            }
            if (Input.GetKey(KeyCode.W)) 
            {
                speedY = jumpSpeed;
                if (!inAir) {
                    playerAnimator.SetTrigger("Jump");
                    inAir = true;
                }
            }

        }
        else 
        {
            speedY -= gravity * Time.deltaTime;
        }
        // Animation configuration

    }
}


