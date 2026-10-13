# Objects required by the Mario device boundary, compiled by the product build.
# Both native and lifecycle probes consume the same current ownership set.
function Get-Dos16DeviceProbeMembers {
    @('platform_dos16_devices.c','platform_dos16_keyboard.c',
      'dos16_raw_keyboard.obj','dos16_pit_clock.obj','dos16_text_cells.obj',
      'dos16_host.obj','dos16_video_mode.obj','kvm_color.obj','kvm_glyph.obj',
      'io_pacing.c','io_control.c','text_elements.c','text_layout.c','ppu_frame.c',
      'platform_dos16_dos_audio.c','platform_dos16_dos_audio_dos.c',
      'platform_dos16_retained_background.c','platform_dos16_compact_vga_layout.c',
      'platform_dos16_planar_row.c','io_planar_frame.c','io_palette_expand.c',
      'platform_dos16_nibble_expand.c','io_palette_pairs.c')
}
