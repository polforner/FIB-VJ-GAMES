using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackPlayer : MonoBehaviour
{
    Vector3 rotate;
    public Animator playerAnimator;
    public Rigidbody bullet;
    public GameManager GM; 
	void Fire()
	{
		Rigidbody bulletClone = (Rigidbody) Instantiate(bullet, transform.position, bullet.transform.rotation * transform.rotation);
        bulletClone.transform.parent = transform.parent;
	}

    // Update is called once per frame
    void Update()
    {
        char c = GM.getArma(); 
        if (Input.GetKeyDown(KeyCode.F)) {
            GM.shoot(); 
            if(c == '2'){
            //playerAnimator.ResetTrigger("MeleeAttack");
            //playerAnimator.SetTrigger("MeleeAttack");
            playerAnimator.Play("Melee Attack");
            }
            else Fire();
        }
    }
}
