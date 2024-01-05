using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class buffChest : MonoBehaviour
{
    private float loot; 
    
    public GameManager GM; 
    
    void Start()
    {
        
    }

    /*void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player"){
            open(); 
        }
    }
    */

    
    private void open(){//se podria cambiar que de un random amount of ammo en range yoqse, +-5
        loot = Random.Range(0, 100); 
        if(loot < 25){//Da extra dmg
            GM.addBuffChest("DMG"); 
        }
        else if(loot < 50){//Da extra HP
            GM.addBuffChest("HP");
        }
        else if(loot < 75){//Da extra lanzas
            GM.addBuffChest("LANZA");
        }
        else{//Da extra durability al melee
            GM.addBuffChest("MELEE");
        }
        GM.addPoints(200); 
        Destroy(GameObject); 
    
    
    }
    
    
    
    void OnCollisionEnter(Collision collision)
    {
        if(collision.collider.tag == "Player")
        {
        Debug.Log ("Player");
        open(); 
        }
    }
}
