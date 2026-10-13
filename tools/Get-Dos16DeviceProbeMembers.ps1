# Objects required by the Mario device boundary, compiled by the product build.
# Both native and lifecycle probes consume the same current ownership set.
function Get-Dos16DeviceProbeMembers {
    @('kvm_platform_dos16_devices.c','kvm_platform_dos16_keyboard.c',
      'dos16_raw_keyboard.obj','dos16_pit_clock.obj','dos16_text_cells.obj',
      'dos16_host.obj','dos16_video_mode.obj','dos16_vga.obj','kvm_color.obj','kvm_glyph.obj','kvm_video.obj','kvm_io_color.c',
      'kvm_io_pacing.c','kvm_io_control.c','kvm_text_elements.c','kvm_text_layout.c','kvm_ppu_frame.c',
      'kvm_io_audio_renderer.c','kvm_platform_dos16_dos_audio.c','kvm_platform_dos16_dos_audio_dos.c',
      'kvm_platform_dos16_retained_background.c','kvm_platform_dos16_compact_vga_layout.c',
      'kvm_platform_dos16_planar_row.c','kvm_io_planar_frame.c','kvm_io_palette_expand.c',
      'kvm_platform_dos16_nibble_expand.c','kvm_io_palette_pairs.c')
}
