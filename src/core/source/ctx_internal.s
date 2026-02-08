.intel_syntax noprefix

kRegSize = 8
kNSavedRegs = 7

kRbxIdx = 0
kRspIdx = 1
kRbpIdx = 2
kR12Idx = 3
kR13Idx = 4
kR14Idx = 5
kR15Idx = 6

.macro StoreReg idx, reg
    mov [rax + \idx * kRegSize], \reg
.endm

.macro LoadReg reg, idx
    mov \reg, [rax + \idx * kRegSize]
.endm

.section .data

ctx_swp_buffer:
    .zero (kRegSize * kNSavedRegs)

.section .text

.extern CoroFuncTrampoline
.extern CoroExit

# rdi -> CoroCtx* other
.global SwapCxt
SwapCxt:
    # store cur ctx to ctx_swp_buffer
    lea rax, [rip + ctx_swp_buffer]

    StoreReg kRbxIdx, rbx
    StoreReg kRspIdx, rsp
    StoreReg kRbpIdx, rbp
    StoreReg kR12Idx, r12
    StoreReg kR13Idx, r13
    StoreReg kR14Idx, r14
    StoreReg kR15Idx, r15
 
    # load old ctx from other
    mov rax, rdi

    LoadReg rbx, kRbxIdx
    LoadReg rsp, kRspIdx
    LoadReg rbp, kRbpIdx
    LoadReg r12, kR12Idx
    LoadReg r13, kR13Idx
    LoadReg r14, kR14Idx
    LoadReg r15, kR15Idx

    # move cur ctx from ctx_swp_buffer to other
    mov r10, rdi
    lea r11, [rip + ctx_swp_buffer]

    xor rcx, rcx # i = 0

.check_move_ctx:
    cmp rcx, kNSavedRegs
    jae .done_move_ctx

    mov rax, [r11 + rcx * kRegSize]
    mov [r10 + rcx * kRegSize], rax

    inc rcx
    jmp .check_move_ctx
.done_move_ctx:

    ret

# rdi -> Coro* coro
.global SetupCtx
SetupCtx:
    mov rax, [rip + kStackFixedSize] # load kStackFixedSize
    mov r10, [rip + kStackOffset] # load kStackOffset

    mov r10, [rdi + r10] # r10 = coro->call_stack
    lea r10, [r10 + rax - kRegSize] # address of stack top

    and r10, -16 # align stack pointer by 16

    mov rax, [rip + kContextOffset] # load kContextOffset
    lea rax, [rdi + rax] # &coro->caller_context

    StoreReg kRspIdx, r10 # rsp <- r10

    lea r11, [rip + CoroFuncTrampoline]
    mov [r10], r11

    lea r11, [rip + CoroExit]
    mov [r10 + kRegSize], r11

    ret

