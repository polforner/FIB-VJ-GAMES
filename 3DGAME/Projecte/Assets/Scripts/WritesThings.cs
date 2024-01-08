using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class WritesThings : MonoBehaviour
{
    public GameManager GM; 
    public Text HP;  
    public Text Ammo; 
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()

    {

        HP.text = "HP: " + GM.returnHUD("hp"); 
        if(GM.returnWeapon() == '1'){
            string aux3 = "Lance: "; 
            aux3 += GM.returnHUD("ammo1"); 
            Ammo.text = aux3; 
            
        }
        else{
            string aux4 = "Sword: "; 
            aux4 += GM.returnHUD("ammo2"); 
            Ammo.text = aux4;
        }
    }
}
