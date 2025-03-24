#include <iostream>
#include <windows.h>   // WinApi header
#include "../BrainTree.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

namespace bt = BrainTree;
bt::BehaviorTree tree;
bt::BehaviorTree tree2;

bt::BehaviorTree *tree4;


//bt::Blackboard::Ptr _Blackboard;


class SayHello : public bt::Node
{
    Status update() override
    {
        std::cout << "Hello, World!" << std::endl;
        return Node::Status::Failure;
    }
};

class SayWow : public bt::Node
{
    Status update() override
    {
        std::cout << "SayWow, World!" << std::endl;
        return Node::Status::Failure;
    }
};
class go 
{ public:

    int golo()
    {
        std::cout << "name run" << std::endl;
        bt::BehaviorTree tree2;

        auto tobo = std::make_shared<bt::Selector>();
        tobo->name = "----Frapper";
        tobo->addChild(std::make_shared<SayHello>());
        tobo->addChild(std::make_shared<SayWow>());
        //tobo->addChild(std::make_shared<Saycheese>());
        tree2.setRoot(tobo);

        for (int i = 0; i < 1; i++)
            tree2.update();

        return 1;
    }
    
};
class Saycheese : public bt::Node
{
    Status update() override
    {
        std::cout << "Saycheese, World!" << std::endl;
        go f ;
        f.golo();
        
        return Node::Status::Running;
    }
};


// new stuff 

class isCharged : public bt::Node
{
    Status update() override
    {
      //  SetConsoleTextAttribute(hConsole, 7);
        setBlackboard(tree4->getBlackboard());
       // setBlackboard(tree.getBlackboard());
       // setBlackboard(tree2.getBlackboard());

        if (   getBlackboard()->getBool("IsCharged")==false) 
        {
            std::cout << "batery is low go back for charge " << std::endl;
            return Node::Status::Failure;

        }     
     //   std::cout << "batery charged " << std::endl;
        return Node::Status::Success;
    }
};

class Charging: public bt::Node
{
    Status update() override
    {
       // SetConsoleTextAttribute(hConsole, 8);
        setBlackboard(tree4->getBlackboard());
       // setBlackboard(tree.getBlackboard());
       // setBlackboard(tree2.getBlackboard());

        if (getBlackboard()->getInt("batteryPower") <100)
        {
            std::cout << "batery is low charging  "<< getBlackboard()->getInt("batteryPower") << std::endl;
           int ch =  getBlackboard()->getInt("batteryPower") + 30; 
           getBlackboard()->setInt("batteryPower", ch);
            return Node::Status::Running;
            
        }
        getBlackboard()->setBool("IsCharged", true);// == true;
      //  std::cout << "batery charged " << std::endl;
        return Node::Status::Success;
    }
};


class isAtPointA : public bt::Node
{
    Status update() override
    {
      //  SetConsoleTextAttribute(hConsole, 2);
        setBlackboard(tree4->getBlackboard());
       // setBlackboard(tree.getBlackboard());
      //  setBlackboard(tree2.getBlackboard());

        if (getBlackboard()->getBool("pointA") == false)
        {
            std::cout << "Drone Needs to move " << std::endl;
            return Node::Status::Failure;

        }
     //  std::cout << "Drone Stay " << std::endl;
        return Node::Status::Success;
    }
};

class GotoPointA : public bt::Node
{
    Status update() override
    {
       // SetConsoleTextAttribute(hConsole, 6);
        setBlackboard(tree4->getBlackboard());
       // setBlackboard(tree.getBlackboard());
       // setBlackboard(tree2.getBlackboard());
        for (int s = 0; s < 2; s++)
        {
            std::cout << "Drone is moving to A " << std::endl;
            Node::Status::Running;

        }
        getBlackboard()->setBool("pointA", true);
     //   std::cout << "Drone is Here at A " << std::endl;
        return Node::Status::Success;
    }
};


class isClear : public bt::Node
{
    Status update() override
    {
      //  SetConsoleTextAttribute(hConsole, 4);
        setBlackboard(tree4->getBlackboard());
      //  setBlackboard(tree2.getBlackboard());

        if (getBlackboard()->getBool("enemyPointA") == true)
        {
            std::cout << "Enemy In zone " << std::endl;
            return Node::Status::Failure;

        }
       std::cout << "Aria Clear " << std::endl;
        return Node::Status::Success;
    }
};


class KillEnemy : public bt::Node
{
   
    Status update() override
    {
      //  SetConsoleTextAttribute(hConsole, 5);
        setBlackboard(tree4->getBlackboard());
      //  setBlackboard(tree.getBlackboard());
       // setBlackboard(tree2.getBlackboard());

        if (getBlackboard()->getBool("enemyPointA"))
        {
           
            std::cout << "Drone fire  " << std::endl;
            return Node::Status::Success;
        }
       
        getBlackboard()->setBool("enemyPointA", false);
        return Node::Status::Failure;
    }
};

void runIt(std::string AgentName , bt::BehaviorTree &tree3 )
{
    if (AgentName == "Free")
    {

     //   SetConsoleTextAttribute(hConsole, 7);
    }
    else
    {
     //   SetConsoleTextAttribute(hConsole, 2);
    }
    std::cout << AgentName << std::endl;
    std::cout << "----------" << std::endl;

    

    auto ChargeSelector = std::make_shared<bt::Selector>();
    //  ChargeSelector->name = "Helth ";
    ChargeSelector->addChild(std::make_shared<isCharged>());
    ChargeSelector->addChild(std::make_shared<Charging>());


    auto aPosition = std::make_shared<bt::Selector>();
    // aPosition->name = "Patrol "; 
    aPosition->addChild(std::make_shared<isAtPointA>());
    aPosition->addChild(std::make_shared<GotoPointA>());


    auto enemyPresent = std::make_shared<bt::Selector>();
    //enemyPresent->name = "-- seek Enemy ";
    enemyPresent->addChild(std::make_shared<isClear>());
    enemyPresent->addChild(std::make_shared<KillEnemy>());


    auto runDrone = std::make_shared<bt::Sequence>();
    runDrone->name = "  autoDrone";
    runDrone->addChild(ChargeSelector);
    runDrone->addChild(aPosition);
    runDrone->addChild(enemyPresent);


    tree3.setRoot(runDrone);


    tree3.getBlackboard()->setBool("pointA", false);
    tree3.getBlackboard()->setBool("IsCharged", false);
    if (AgentName == "Free")
    {
        tree3.getBlackboard()->setInt("batteryPower", 10);
    }
    else
    {
        tree3.getBlackboard()->setInt("batteryPower", 80);
    }



   
}


int main()
{
    runIt("Topman" , tree);
    runIt("Free" , tree2);

    int t = 0, z = 0;
    // simulate 5 frames
    for (int i = 0; i < 206; i++)
    {
 

        bool randbool = rand() & 1;
        bool randbool2 = rand() & 1;
        //Drone 1
        //allocating Black boar Mem for the nodes 
        tree4 = &tree;

        tree.getBlackboard()->setBool("enemyPointA", randbool);
        t = tree.getBlackboard()->getInt("batteryPower");   

        if (t < 30)
        {
            tree.getBlackboard()->setBool("IsCharged", false);
            tree.getBlackboard()->setBool("pointA", false);
        }
        else {
            tree.getBlackboard()->setInt("batteryPower", t - 5);
            tree.getBlackboard()->setBool("IsCharged", true);
        }
        SetConsoleTextAttribute(hConsole,9);
        tree.update();
       

        //Drone 2 
        //allocating Black boar Mem for the nodes 
        tree4 = &tree2; 
        tree2.getBlackboard()->setBool("enemyPointA", randbool2);
        z = tree2.getBlackboard()->getInt("batteryPower");
        if (z < 50)
        {
            tree2.getBlackboard()->setBool("IsCharged", false);
            tree2.getBlackboard()->setBool("pointA", false);
        }
        else {
            tree2.getBlackboard()->setInt("batteryPower", t - 5);
            tree2.getBlackboard()->setBool("IsCharged", true);
        }
    
        SetConsoleTextAttribute(hConsole, 2);
        tree2.update();

    }
  
   
    return 0;
}
