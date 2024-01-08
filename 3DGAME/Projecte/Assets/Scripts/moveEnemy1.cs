using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class moveEnemy1 : MonoBehaviour
{
    int direccion = 1; 
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(transform.position.x >= 24) direccion = -1; 
        if(transform.position.x <= 14) direccion = 1; 
        float aux = (transform.position.x);
        aux *= (0.5f * direccion); 

        transform.position = new Vector3(aux,  (transform.position.y), (transform.position.z)); 
    }
}
