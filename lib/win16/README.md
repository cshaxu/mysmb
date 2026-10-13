# Win16 receiving contract

`mygames_win16_contract` is a C90 interface target linked to KVM. It currently
declares application callbacks only; it provides no USER/GDI implementation,
NE linker route or running Mario Win16 product.

Each application supplies a context, title and supported views. Input callbacks
receive neutral physical events; the application decides what they mean.
The app reports its requested presentation and exit state, and supplies text
frames or synchronous graphics bands. A future host owns event dispatch,
timing, GDI devices and window lifetime. It must consume callbacks without
assigning Tab, mouse, keyboard or gameplay meanings.

The contract fixture proves app-owned input can select a view and exit through
this ABI. It is a native compile/contract test, not Win3.x runtime evidence.
The later Mine import must supply reviewed generic USER/GDI implementation
and real NE/MZ build and runtime qualification before claiming Win16 support.
