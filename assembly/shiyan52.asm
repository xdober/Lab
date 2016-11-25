.386
.model flat,c
.code
public JudStu,CalAve
JudStu proc par1:dword,par2:dword,par3:dword
		mov ecx,par2;学生人数
		mov ebx,par1;学生起始地址
		mov edi,par3;姓名缓冲区地址
	loop2:
		mov esi,edi
		mov edx,0
	loop1:
		mov al,[esi][edx]
		cmp al,[ebx][edx]
		jnz loop3
		inc edx
		cmp edx,9
		jz eend
		jmp loop1
	loop3:
		add ebx,14
		dec ecx
		cmp ecx,0
		jz eend
		jmp loop2
	eend:
		ret
JudStu endp

CalAve proc par1:dword,par2:dword
	mov esi,par1
	mov ecx,par2
	mov eax,0
gnt:
	mov al,10[esi]
	sal eax,2
	mov edx,0
	mov dl,11[esi]
	sal edx,1
	add edx,eax
	mov eax,0
	mov al,12[esi]
	add eax,edx
	mov edx,0
	mov bl,7
	div bl
	mov 13[esi],al
	add esi,14
	mov eax,0
	dec ecx
	jnz gnt
	ret
CalAve endp
	end