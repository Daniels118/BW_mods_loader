#include "ddraw.h"

extern ddrawDll ddraw;

typedef HRESULT(_stdcall* DDrawCreateProc)(void* a, void* b, void* c);

HRESULT _stdcall FakeDirectDrawCreate(void* a, void* b, void* c) {
	DDrawCreateProc proc = (DDrawCreateProc)ddraw.DirectDrawCreate;
	if (!proc) return -1;
	return proc(a, b, c);
}

__declspec(naked) void FakeAcquireDDThreadLock() {
	_asm jmp[ddraw.AcquireDDThreadLock];
}

__declspec(naked) void FakeCheckFullscreen() {
	_asm jmp[ddraw.CheckFullscreen];
}

__declspec(naked) void FakeCompleteCreateSysmemSurface() {
	_asm jmp[ddraw.CompleteCreateSysmemSurface];
}

__declspec(naked) void FakeD3DParseUnknownCommand() {
	_asm jmp[ddraw.D3DParseUnknownCommand];
}

__declspec(naked) void FakeDDGetAttachedSurfaceLcl() {
	_asm jmp[ddraw.DDGetAttachedSurfaceLcl];
}

__declspec(naked) void FakeDDInternalLock() {
	_asm jmp[ddraw.DDInternalLock];
}

__declspec(naked) void FakeDDInternalUnlock() {
	_asm jmp[ddraw.DDInternalUnlock];
}

__declspec(naked) void FakeDSoundHelp() {
	_asm jmp[ddraw.DSoundHelp];
}

__declspec(naked) void FakeDirectDrawCreateClipper() {
	_asm jmp[ddraw.DirectDrawCreateClipper];
}

__declspec(naked) void FakeDirectDrawCreateEx() {
	_asm jmp[ddraw.DirectDrawCreateEx];
}

__declspec(naked) void FakeDirectDrawEnumerateA() {
	_asm jmp[ddraw.DirectDrawEnumerateA];
}

__declspec(naked) void FakeDirectDrawEnumerateExA() {
	_asm jmp[ddraw.DirectDrawEnumerateExA];
}

__declspec(naked) void FakeDirectDrawEnumerateExW() {
	_asm jmp[ddraw.DirectDrawEnumerateExW];
}

__declspec(naked) void FakeDirectDrawEnumerateW() {
	_asm jmp[ddraw.DirectDrawEnumerateW];
}

__declspec(naked) void FakeGetDDSurfaceLocal() {
	_asm jmp[ddraw.GetDDSurfaceLocal];
}

__declspec(naked) void FakeGetOLEThunkData() {
	_asm jmp[ddraw.GetOLEThunkData];
}

__declspec(naked) void FakeGetSurfaceFromDC() {
	_asm jmp[ddraw.GetSurfaceFromDC];
}

__declspec(naked) void FakeRegisterSpecialCase() {
	_asm jmp[ddraw.RegisterSpecialCase];
}

__declspec(naked) void FakeReleaseDDThreadLock() {
	_asm jmp[ddraw.ReleaseDDThreadLock];
}