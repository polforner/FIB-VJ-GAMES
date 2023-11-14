using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class GameManager : MonoBehaviour
{
    public static GameManager Instance { get; private set; }
    
    private vector<int> ammo; 
    private int hp; 
    

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Debug.Log("Demasiados GameManager");
        }
    }

    public void loadNextScene()
    {
        int currentScene = SceneManager.GetActiveScene().buildIndex;

        SceneManager.LoadScene(currentScene++);
    }

    public void restartLevel()
    {
        int currentScene = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(currentScene++);
    }

    public int getAmmo(int a){
      if(a>1) return -1; 
      else return ammo[a]; 

    }
    

    //Funcion que se llama cada vez que dispara el arma 
    public void shoot(int weapon){
      ammo[weapon]--; 
    }
}
