#include "GameObject.h"


int main()
{
	shared_ptr<GameObject> obj = make_shared<GameObject>();
	shared_ptr<Transform> tr = make_shared<Transform>();
	

	obj->AddComponent(tr);

	auto tr2 = obj->GetComponent<Animator>();

	return 0;
}