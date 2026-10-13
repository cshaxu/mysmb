# Mine KVM tests

application_test.c owns gesture cancellation, command/input mapping, hit
regions, view requests and clock policy. presentation_test.c owns authored
cells/bands, bounds, palette slots and number formatting. Mine's private-
desktop integration target exercises actual window/Console startup, mouse,
keys, retained Tab and exit. DOS/Win3.x joins use the neutral SDL test proxy
under ignored build, with installed DOSBox CPU/cycles unchanged.
