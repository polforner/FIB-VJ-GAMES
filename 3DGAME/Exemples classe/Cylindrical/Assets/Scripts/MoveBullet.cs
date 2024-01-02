using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveBullet : MonoBehaviour
{
    public float rotationSpeed;
    double liveTime;
    Vector3 startDirection;
    Quaternion startRotation;
    // Start is called before the first frame update
    void Start()
    {
        liveTime = 360.0f / rotationSpeed;
        
        startRotation = transform.rotation;
        startDirection = transform.position - transform.parent.position;
        startDirection.y = 0.0f;
        startDirection.Normalize();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        liveTime -= Time.deltaTime;
        if (liveTime <= 0.0) Destroy(gameObject);
        else {
            float angle;
            Vector3 direction;

            angle = rotationSpeed * Time.deltaTime;
            direction = transform.position - transform.parent.position;
            transform.position = transform.parent.position + Quaternion.AngleAxis(-angle, Vector3.up) * direction;
            Physics.SyncTransforms();

            //correct orientation
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
        }
    }
}
