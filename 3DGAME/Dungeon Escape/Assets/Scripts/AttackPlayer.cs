using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackPlayer : MonoBehaviour
{
    Vector3 rotate;
    public Animator playerAnimator;
    public Rigidbody bullet;
	void Fire()
	{
		Rigidbody bulletClone = (Rigidbody) Instantiate(bullet, transform.position, bullet.transform.rotation * transform.rotation);
        bulletClone.transform.parent = transform.parent;
	}

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.P)) {
            //playerAnimator.ResetTrigger("MeleeAttack");
            //playerAnimator.SetTrigger("MeleeAttack");
            playerAnimator.Play("Melee Attack");
        }

        if (Input.GetKeyDown(KeyCode.L)) {    
            Fire();
        }
    }
}
