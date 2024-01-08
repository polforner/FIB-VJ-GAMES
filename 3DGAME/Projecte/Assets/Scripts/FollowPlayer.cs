using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPlayer : MonoBehaviour
{
    public GameObject player;

    Vector3 startDirection;
    float playerStartY;
    float cameraStartY;
    Vector3 spawn; 

    // Start is called before the first frame update
    void Start()
    {
        spawn = transform.position; 
        // Store starting direction of the player with respect to the axis of the level
        startDirection = player.transform.position - player.transform.parent.position;
       startDirection.y = 0.0f;
       playerStartY = player.transform.position.y;
       cameraStartY = transform.parent.position.y;
        startDirection.Normalize();
    }

    // Update is called once per frame
    void Update()
    {
        // Compute current direction
        Vector3 currentDirection = player.transform.position - player.transform.parent.position;
        currentDirection.y = 0.0f;
        currentDirection.Normalize();
        // Change orientation of the camera pivot to match the player's
        Quaternion orientation;
        if ((startDirection - currentDirection).magnitude < 1e-3)
            orientation = Quaternion.AngleAxis(0.0f, Vector3.up);
        else if ((startDirection + currentDirection).magnitude < 1e-3)
            orientation = Quaternion.AngleAxis(180.0f, Vector3.up);
        else
            orientation = Quaternion.FromToRotation(startDirection, currentDirection);
        transform.parent.rotation = orientation;

        // Compute the position of the camera pivot
        
        Vector3 position = transform.parent.position;
        position.y = cameraStartY + (player.transform.position.y - playerStartY);
        transform.parent.position = position;
        
    }
}
