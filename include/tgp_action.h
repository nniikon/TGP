#ifndef TGP_ACTION_H_
#define TGP_ACTION_H_

namespace tgp {

class Action {
public:
    virtual void operator()() = 0;

    virtual void   Do()      = 0;
    virtual bool Undo()      = 0;
    virtual void SaveState() = 0;
};

}; // namespace 

#endif // TGP_ACTION_H_
