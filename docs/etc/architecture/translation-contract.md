# Translation Contract Detail

Every C translation unit identifies the reviewed assembly source and inclusive address range, RAM and register assumptions, frame/NMI context, and reference trace cases. Code/data coverage is complete only when every admitted PRG byte has one documented disposition.

Validation compares neutral state checkpoints: RAM, registers where relevant, object slots, scroll state, OAM-equivalent commands, PPU/APU command streams, and frame result. Rendering similarity is not proof of translation correctness.
