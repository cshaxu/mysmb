/* Private entry hook for the original large-model DOS C runtime.
 * main(void) does not consume argc/argv. Keep environment setup and PSP-based
 * executable-path discovery, but avoid unused persistent argument storage.
 * Review this hook before introducing any parsed command-line consumer.
 * /AL supplies the far return convention expected by the runtime caller. */
void _setargv(void)
{
}
