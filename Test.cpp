#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "AppStore.h"

void test_bst1_insert() {
	AppStore appS;
	App a1("Angry Birds", 2.99, "Games", "fsafsa");
	App a2("Badland", 1.99, "APG", "sfasfq");
	App a3("Castelvania", 1.99, "Bdventure", "qsfafasfsq");
	App a4("Dreadlord", 1.99, "NOIDEA", "qsafasfq");
	App a5("WTF", 989.99, "Random", "safasfaf");
	App a6("WTF", 989.99, "Random", "safasfaf");

	a4.classificar(5);
	a5.classificar(1);

	a3.classificar(2);
	a2.classificar(2);

	a1.classificar(1);
	a6.classificar(1);

	appS.BSTInsertApp(&a1);
	appS.BSTInsertApp(&a2);
	appS.BSTInsertApp(&a3);
	appS.BSTInsertApp(&a4);
	appS.BSTInsertApp(&a5);
	appS.BSTInsertApp(&a6);

	BST<App*> bst = appS.BSTGetApps();


	BSTItrIn<App*> it(bst);

	ASSERT_EQUAL("Dreadlord", it.retrieve()->getName());
	it.advance();
	ASSERT_EQUAL("Badland", it.retrieve()->getName());

}

void runBST() {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_bst1_insert));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "BST Tests");
}

