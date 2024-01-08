using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lootChest : MonoBehaviour
{
    // Start is called before the first frame update
    private float loot; 
    
    public GameManager GM; 
    
    void Start()
    {
        
    }

    void Update(){

    }

    
    public void open(){//se podria cambiar que de un random amount of ammo en range yoqse, +-5
        loot = Random.Range(0, 100); 
        if(loot < 25){//25% de las veces da ammo de arma 1
            GM.addLootChest("A1", 15); 
        }
        else if(loot < 50){//25% de las veces da ammo de arma 2
            GM.addLootChest("A2", 5);
        }
        else if(loot < 75){//25% de las veces da HP
            GM.addLootChest("HP", 20);
        }
        else if(loot < 95){//20% de las veces da nada
        }
        else{//5% de las veces explota
            GM.takeDamage(10); 
        }
        
    Destroy(gameObject); 
    
    }
    
    void OnCollisionEnter(Collision col){
        Debug.Log("col"); 
            open(); 
    }
    

}
