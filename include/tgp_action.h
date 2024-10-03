#ifndef TGP_ACTION_H_
#define TGP_ACTION_H_

namespace tgp {

class Action {
public:
    void operator()();

    virtual void   Do()      = 0;
    virtual bool Undo()      = 0;
    virtual bool SaveState() = 0;

    virtual ~Action() = default;
};

}; // namespace 

#endif // TGP_ACTION_H_
