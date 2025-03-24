# BrainTree

A C++ [behavior tree] single header library.

## Features

- behavior tree implementation
- predefined composites
- predefined decorators
- (optional) rudimentary blackboard
- (optional) behavior tree builders

## Install

Include `BrainTree.h` in your project.

## Example

```c++
// this example should print out "Hello, World!", four times
#include <iostream>
#include "BrainTree.h"

class Action : public BrainTree::Node
{
public:
    Status update() override
    {
        std::cout << "Hello, World!" << std::endl;
        return Node::Status::Success;
    }
};

void CreatingBehaviorTreeManually()
{
    BrainTree::BehaviorTree tree;
    auto sequence = std::make_shared<BrainTree::Sequence>();
    auto sayHello = std::make_shared<Action>();
    auto sayHelloAgain = std::make_shared<Action>();
    sequence->addChild(sayHello);
    sequence->addChild(sayHelloAgain);
    tree.setRoot(sequence);
    tree.update();
}



int main()
{
    CreatingBehaviorTreeManually();
      return 0;
}
```

## Composites

| Composite        | Behaviour                                                                       | Success                 | Running               | Failure              |
| ---------------- | ------------------------------------------------------------------------------- | ----------------------- | --------------------- | -------------------- |
| Selector         | Ticks each child node in order, starting from the beginning each tick           | If a child succeeds     | If a child is running | If all children fail |
| Sequence         | Ticks each child node in order, starting from the beginning each tick           | If all children succeed | If a child is running | If a child fails     |
| StatefulSelector | Ticks each child node in order, starting from the child ticked in previous tick | If a child succeeds     | If a child is running | If all children fail |
| StatefulSequence | Ticks each child node in order, starting from the child ticked in previous tick | If all children succeed | If a child is running | If a child fails     |

## Decorators

| Decorator    | Behaviour                                                 |
| ------------ | --------------------------------------------------------- |
| Succeeder    | Always returns success                                    |
| Failer       | Always returns failure                                    |
| Inverter     | Inverts the result of the child node                      |
| Repeater     | Repeats until child node succeeds (infinitely or limited) |
| UntilSuccess | Repeats until child node succeeds                         |
| UntilFailure | Repeats until child node fails                            |



## License

MIT (c), Jonathan James 2024-2025
