/* Private entry hooks for the original large-model DOS C runtime.
 * main(void) uses neither argc/argv nor a C environment vector. The original
 * envp copy can overflow its 16-bit allocation size for a dense environment.
 * Keep cinit, the DOS PSP environment and PSP-based executable-path discovery;
 * omit only the unused C argument/environment copies. The build checks their
 * consumers; review these hooks before introducing either capability.
 * /AL supplies the far return convention expected by the runtime caller. */
void _setargv(void)
{
}
void _setenvp(void)
{
}
