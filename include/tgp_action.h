#ifndef TGP_ACTION_H_
#define TGP_ACTION_H_

namespace TGP {

class Action {
public:
    virtual void operator()();
};

class ReversableAction : public Action {
public:
    virtual void Reverse();
};

}; // namespcae

#endif // TGP_ACTION_H_
