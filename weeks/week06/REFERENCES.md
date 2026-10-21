# 06회차 공식 자료와 근거 기록

조회 기준일: **2026-10-17**. 아래 `p`는 문서 하단의 **인쇄 페이지**이며 PDF Viewer의 페이지 번호와 다를 수 있습니다. 자료의 사실, 이번 요청서의 정책, Host Test 결과를 구분해 기록하세요.

## 먼저 대상과 문서의 역할을 확인합니다.

이번 회차는 05회차와 같은 **TC387QP / TC38x 계열**을 대상으로 합니다. Part 비교 기준은 **SAK-TC387QP-160F300S AE, PG-LFBGA-292**입니다. 공식 예제의 Board는 **KIT_A2G_TC387_5V_TFT**입니다. Host 과제는 이 Board에 바로 Flash하는 전체 Firmware가 아닙니다.

| ID | 공식 자료 | 찾아야 할 부분 |
| --- | --- | --- |
| D0 | [TC38x Data Sheet Addendum](https://www.infineon.com/assets/row/public/documents/10/49/infineon-tc38x-addendum-datasheet-en.pdf), v1.9, 2025-12 | Table 1 p3의 정확한 Part Number·Package·제품 사양. F300S의 CPU 최대 300 MHz를 STM Clock으로 사용하지 않습니다. Table 2 p6의 F400S 등 제품 차이도 구분합니다. |
| D1 | [TC38x Datasheet](https://www.infineon.com/dgdl/Infineon-TC38x-DataSheet-v01_02-EN.pdf?fileId=5546d4626f229553016fb316e6cf748b), V1.2, 2021-03 | §2.2 BGA292, §3.4 p291부터 Operating Conditions, §3.5 p294부터 Pad 조건. Part·Package·전기적 제한을 확인하는 자료입니다. |
| U1 | [TC3xx User Manual Part 1](https://www.infineon.com/assets/row/public/documents/10/44/infineon-aurix-tc3xx-part1-usermanual-en.pdf), V2.0.0, 2021-02 | §16.4.1.1.1 p16-4의 SRC 구성, §16.4.1.4~7 p16-9의 CLRR·SRE·SRR·TOS. 요청 발생, 전달 허용, 처리 대상을 구분합니다. |
| U2 | [TC3xx User Manual Part 2](https://www.infineon.com/assets/row/public/documents/10/44/infineon-aurix-tc3xx-part2-usermanual-en.pdf), V2.0.0, 2021-02 | §27.3.2 p27-5의 Compare match, §27.4.4 p27-16의 CMP0IR와 Note, p27-18의 CMP0IRR. |
| U3 | [System Timer 공식 설명](https://documentation.infineon.com/aurixtc3xx/docs/wvt1713281569556) | Feature list / Functional description의 64-bit Free-running Counter, CMP0/1, TIM0~6와 CAP. |
| A1 | [AP32381: TC3xx startup and initialisation](https://documentation.infineon.com/aurixtc3xx/docs/nyb1710229964455) | CPU Interrupt and Trap handling의 BIV, CPU ICR.IE, Interrupt와 Trap의 제어 범위. |

Datasheet는 정확한 제품과 허용 조건을 확인하는 출발점입니다. **Interrupt 처리 순서와 Register 의미는 User Manual**, API의 실제 동작은 **iLLD Source**에서 확인합니다. 10ms, Mailbox 용량 4, 병합·Overflow 정책은 이번 요청서가 정한 값입니다.

## 학습 목표에 따라 읽고 증거를 남깁니다.

| 학습 목표 | 확인할 근거와 질문 | CONCURRENCY.md에 남길 내용 |
| --- | --- | --- |
| Polling / Interrupt 비교 | U3에서 Compare가 무엇을 발생시키는지 확인합니다. U1의 TOS·SRPN·SRE와 A1의 CPU ICR.IE·Vector table을 연결합니다. Main 지연과 IRQ 차단은 같은 상황인가요? | 두 흐름도, `Timer event → ISR → Main 처리`의 서로 다른 시각, 선택 이유와 적용 조건. |
| 짧은 ISR / Main 분리 | S1·S2·S3에서 다음 Compare를 어떻게 예약하는지 추적합니다. ISR 진입이 늦어졌을 때 기준을 현재 시각으로 바꾸면 주기는 어떻게 되나요? | ISR과 Main의 업무 표, Context·호출 횟수 Test, 10ms 전에 다음 Compare를 설정해야 하는 조건. |
| Race condition / Atomicity | C1·C2에서 volatile과 atomic의 보장 범위를 비교합니다. S4의 IRQ 상태 저장·복원을 읽습니다. 공유값을 읽은 뒤 초기화하기 전에 ISR이 실행되면 어떤 값이 남나요? | 읽기·초기화 사이의 Race timeline, 일관된 Snapshot 범위, 진입 전 IRQ가 false인 Case, Critical section 시간 B의 영향. |

## 공식 예제를 함수와 Register까지 추적합니다.

기준 Repository는 `Infineon/AURIX_code_examples`, 고정 Commit은 **6759d2845feaac0107b785fe6bc57ed785c3f4fc**입니다. 예제 경로는 `code_examples/STM_Interrupt_1_KIT_TC387_TFT`이며, 이 경로의 Source를 직접 확인했습니다.

| ID | 고정 Source | 읽을 위치·확인할 연결 |
| --- | --- | --- |
| S1 | [STM_Interrupt.c](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/STM_Interrupt.c#L41) | L41~45의 Priority·STM, L71~78의 IFX_INTERRUPT와 ISR, L88~97의 TOS. 예제는 CPU0·Priority 40·500ms이며, 이번 10ms 요구와 구분합니다. |
| S2 | [IfxStm.c](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/Libraries/iLLD/TC38A/Tricore/Stm/Std/IfxStm.c#L163) | L163~226의 initCompare, L229~238의 기본 Config. Comparator, 비교 범위, output, SRC 설정을 연결합니다. |
| S3 | [IfxStm.h](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/Libraries/iLLD/TC38A/Tricore/Stm/Std/IfxStm.h#L595) | L595~609의 주파수·TIM0 조회, L672~675의 increaseCompare, L715~718의 updateCompare. 두 Compare API가 같은 의미인지 확인합니다. |
| S4 | [IfxCpu.h](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/Libraries/iLLD/TC38A/Tricore/Cpu/Std/IfxCpu.h#L743) | L743~758의 areInterruptsEnabled / disableInterrupts, L1028~1034의 restoreInterrupts. 반환값과 false 인자의 동작을 확인합니다. |
| S5 | [IfxSrc.h](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/Libraries/iLLD/TC38A/Tricore/Src/Std/IfxSrc.h#L247) | L247~276의 clearRequest / enable / init. CLRR·SRE·SRPN·TOS와 대응시킵니다. |
| S6 | [IfxStm.c: clearCompareFlag](https://github.com/Infineon/AURIX_code_examples/blob/6759d2845feaac0107b785fe6bc57ed785c3f4fc/code_examples/STM_Interrupt_1_KIT_TC387_TFT/Libraries/iLLD/TC38A/Tricore/Stm/Std/IfxStm.c#L54) | L54~64의 ISCR.CMP0IRR / CMP1IRR. S5의 SRC 요청 처리와 비교합니다. |

[TC387 STM Training](https://www.infineon.com/dgdl/Infineon-STM_Interrupt_1_KIT_TC387_TFT-Training-v01_01-EN.pdf?fileId=5546d4627a0b0c7b017a5840f03e248d)의 p6~7도 함께 읽을 수 있습니다. 다만 p2의 Counter reset 표현은 U3의 Free-running 설명 및 S1·S3 구현과 대조해야 합니다. 다음 주기는 **Counter reset이 아니라 Compare 갱신**으로 설명하세요.

## 세 가지 혼동을 확인합니다.

1. **STM flag / SRC request / Mailbox pending**: U2 p27-16 Note에서 CMP0IR은 새 Compare Interrupt를 차단하는 gate가 아님을 확인하세요. U1 p16-9의 SRC.SRR은 정상 Interrupt acknowledge 시 Hardware가 clear합니다. 두 상태 모두 Software 요청 개수를 저장하는 Mailbox와 다릅니다. `platform_timer_service`는 이 과제의 Host 서비스 경계입니다.
2. **이전 상태 복원 / 무조건 enable**: S4의 restore(false)는 아무 동작도 하지 않습니다. 이전 상태를 복원하려면 Critical section 중간에 임의로 enable하지 않아야 합니다. CPU0 mask가 다른 Core·DMA·Trap까지 막는다고 해석하지 마세요.
3. **volatile / 원자적 묶음 처리**: [C1: GCC Volatiles](https://gcc.gnu.org/onlinedocs/gcc/Volatiles.html)는 volatile이 non-volatile 메모리의 barrier가 아님을 설명합니다. [C2: WG14 N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)의 §6.7.3¶7 p122와 §6.5.2.4¶2 p85를 비교하세요. 개별 접근의 특성과 여러 동작 전체의 Atomicity는 별도입니다.

## 근거 기록 양식

| 문서 ID·Version·절·함수 | 읽은 사실 | 적용 조건 | 설계 판단 | 검증 방법·실제 결과 |
| --- | --- | --- | --- | --- |
| 직접 채우기 | 문서의 어떤 항목을 읽었는지 | CPU·동시 접근 주체·Clock 등 | 요구사항과 연결한 판단 | Test 이름·관찰값 또는 미측정 사항 |

지연 분석의 **Sensor 2ms + Publish 15ms**는 요청서의 가정이며 실측 결과가 아닙니다. 짧은 Critical section의 시간은 **B**로 두고 추가 차단 시간과 전체 Interrupt latency를 구분합니다. Host에서 통과한 Test만으로 B나 실제 MCU의 Worst-case latency를 증명할 수는 없습니다.
