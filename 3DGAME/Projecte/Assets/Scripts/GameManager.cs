using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class GameManager:MonoBehaviour
{
    public static GameManager Instance { get; private set; }
    
    //Municion en reserva de cada una de las armas. 
    private int[] ammo = {20, 0};
    //Municion actual para cada una de las armas. 
    private int[] clip = {20, 5};
    //Valores máximos de ciertos parámetros. 
    //Por orden: 
    // max[0] = ammo max lanzas, max[1] = ammo max melee, max[2] = hp max
    private int[] max = {100, 50, 100};
    //Vida actual del jugador 
    private int hp; 
    //Nombre de la escena en la que nos encontramos. 
    private string sceneName; 
    //Vidas actuales del jugador. Empieza en 3 y llega hasta 0. 
    private int lives; 
    //Caracter que guarda el arma actual: '1' para lanzas, '2' para melee. 
    private char armaActual;
    //Modificador al daño. 
    private int baseDmg;
    //Dice si estamos jugando actualmente o no. 
    private bool playing; 
    
    //Para debugar los profes: indica si estamos en invulnerable. 
    private bool star;

    private bool paused; 
    

    private void Awake()
    {
        lives = 3; 
        paused = false; 
        playing = false; 
        baseDmg = 0;  
        armaActual = '1'; 
        hp = 100; 
        star = false; 
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
            Debug.Log("GameManager creado"); 
        }
        else
        {
            Debug.Log("Demasiados GameManager");
        }
    }

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.G)){
            star = !star; 
            if(star)Debug.Log("DEBUG: Godmode ON");
            else Debug.Log("DEBUG: Godmode OFF"); 
        }
        else if (Input.GetKeyDown(KeyCode.M)){
            ammo[0] = max[0]; 
            ammo[1] = max[1]; 
            clip[0] = 25; 
            clip[1] = 10; 
            Debug.Log("DEBUG: Max ammo! Lance: " + ammo[0] + ", sword: " + ammo[1] + ".");
        }
        else if (Input.GetKeyDown(KeyCode.Y)){
            baseDmg += 100;
            hp += 100; 
            max[2] += 100; 
            Debug.Log("DEBUG: Aumentado el daño y vida: " + baseDmg + " dmg, " + hp + " hp.");
        }
        else if(Input.GetKeyDown(KeyCode.Alpha9)){
            loadScene("Victory"); 
        }
        else if (Input.GetKeyDown(KeyCode.I)){
            takeDamage(50); 
        }
                else if (Input.GetKey(KeyCode.Alpha1)){
            if(SceneManager.GetActiveScene().name == "Half1")armaActual = '1'; 
            else if (!playing) loadScene("Inicio");
            
        }
        else if (Input.GetKey(KeyCode.Alpha2)){
            if(SceneManager.GetActiveScene().name == "Half1")armaActual = '2'; 
            else if (!playing) loadScene("Instrucciones");
        }
        else if (Input.GetKey(KeyCode.Alpha3)){
            if(SceneManager.GetActiveScene().name == "Half1" && paused) loadScene("Inicio");
            else if (!playing)loadScene("Creditos"); 
        }
        else if (Input.GetKey(KeyCode.R)){
            reloadGun(); 
        }   
        else if (Input.GetKeyDown(KeyCode.P)){
            if(SceneManager.GetActiveScene().name != "Half1"){
                loadScene("Half1");
                playing=true; 
            }
            else paused = !paused; 
        }
    }

    public void setStar(bool b){
        star = b; 
    }

    //Carga una escena dado el nombre de esta.
    public void loadScene(string a){
        SceneManager.LoadScene(a); 
    }

    //Reinicia el nivel. Se llama principalmente al perder una vida. 
    public void restartLevel()
    {
        hp = 100; 
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }


    //Devuelve las  balas que tiene el arma actual(probs cero usages pero meh)
    public int getClip(int a){
      if(a>1) return -1; 
      else return clip[a]; 

    }
    

    //Funcion que se llama cada vez que dispara el arma, devuelve false si no quedan balas y true en caso contrario
    public bool shoot(){
        int weapon = armaActual - '1'; 
      if(clip[weapon] ==0) return false; 
      else{
        clip[weapon]--; 
        if(clip[weapon] == 0) reloadGun();
        Debug.Log("Disparo el arma" + armaActual + ", municion:" + clip[weapon]);
        return true;  
      }
      
    }

    public int getWeapon(){
        return armaActual - '0'; 
    }
    
    //Recibe damage. Si la vida es menor a cero, pierde. 
    public void takeDamage(int amount){
        if(star) return; 
        hp = hp - amount;
        if(hp <= 0) lose();   
    }

    //Gana vida. Viene de cofres. 
    public void gainHealth(int amount){
        hp += amount; 
        if(hp > max[2]) hp = max[2]; 
    }

    //Recarga el arma actual
    public void reloadGun(){
        int weapon = armaActual - '0'; 
        if(weapon == 1){
            if(clip[0] == 25)return; 
            else{
                int bulletsAdded = 25 - clip[0];
                if(bulletsAdded > ammo[0]){
                    clip[0] += ammo[0]; 
                    ammo[0] = 0; 
                    return; 
                } 
                else{
                    clip[0] += bulletsAdded; 
                    ammo[0] -= bulletsAdded; 
                    return;
                }
            }
        }
        else{
            if(clip[1] == 10)return; 
            else{
                int bulletsAdded = 10 - clip[1];
                if(bulletsAdded > ammo[1]){
                    clip[1] += ammo[1]; 
                    ammo[1] = 0; 
                    return; 
                } 
                else{
                    clip[1] += bulletsAdded; 
                    ammo[1] -= bulletsAdded; 
                    return;
                }
            }

        }
    }

    public char getArma(){
        return armaActual; 
    }

    public int dealDmg(){
        if(armaActual == '1'){//lanza
            return 20+baseDmg; 
        }
        else return 40+baseDmg;
    }

    public void addLootChest(string cosa, int amount){
        if(cosa == "A1"){
            ammo[0] += amount; 
            if(ammo[0] > max[0]) ammo[0] = max[0]; 
        }
        else if(cosa == "A2"){
            ammo[1] += amount; 
            if(ammo[1] > max[1]) ammo[1] = max[1]; 
        }
        else if(cosa == "HP"){
            gainHealth(amount); 
        }
        Debug.Log("He conseguido " + cosa); 
    }

    public void addBuffChest(string cosa){
        if(cosa == "ATK"){
            baseDmg += 5; 
        }
        else if(cosa == "HP"){
            max[2] += 10; 
            hp += 10; 
        }
        else if(cosa =="LANZA"){
            ammo[0] += 10; 
            max[0] += 10; 
            ammo[1] += 3; 
            max[1] += 3; 
        }
        else{
            lives++; 
        }
    }

    public void lose(){
        lives--; 
        if(lives == 0){
            loadScene("GameOver"); 
            playing = false; 
        }
        else{
             
            restartLevel();
            
            Debug.Log("Pierde una vida. Restantes: " + lives);
        }
    }

    public void win(){
        loadScene("Victory"); 
        playing = false; 
        
    }

    public string returnHUD(string req){
        string ret = "";
        if(req == "hp"){
            ret += hp; 
            ret += "/"; 
            ret += max[2]; 
        }
        else if(req == "ammo1"){
            ret += clip[0]; 
            ret += "/"; 
            ret += ammo[0]; 
        }
        else if(req == "ammo2"){
            ret += clip[1]; 
            ret += "/"; 
            ret += ammo[1]; 
        }
        else if(req == "vidas"){ 
            for(int i = 0; i < lives; ++i) ret += "<3";
        }
        return ret; 
    }

    public char returnWeapon(){
        return armaActual; 
    }
}
