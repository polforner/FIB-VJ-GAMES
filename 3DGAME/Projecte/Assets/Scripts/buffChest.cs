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


    
    public void open(){
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
    Destroy(gameObject);
    
    }

    void OnCollisionEnter(Collision col){
        Debug.Log("buff"); 
        open(); 
    }
}
