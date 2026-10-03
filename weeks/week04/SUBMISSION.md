# 4주차 과제를 Fork부터 Pull Request까지 제출하기

아래 명령은 Git Bash 또는 macOS/Linux Terminal 기준입니다. `YOUR_GITHUB_ID`를 자신의 GitHub 아이디로 바꿔 실행합니다. 실제 명령에 꺾쇠 괄호를 넣지 않습니다.

제출은 **C 구현 → Host test → Build 단계 확인 → Commit → Push → 원본 저장소에 PR** 순서입니다. 원본 코드와 다른 학생 폴더를 보존하기 위해 자기 `submissions/week04/YOUR_GITHUB_ID/`만 변경합니다.

## 1. 처음 한 번 Fork하고 Clone하기

GitHub에서 [원본 저장소](https://github.com/zinee-u/embedded-just-for-fun)를 열고 **Fork**를 눌러 자기 계정에 복사합니다. 이미 Fork와 Clone이 있다면 이 단계는 건너뛰세요.

```sh
git clone https://github.com/YOUR_GITHUB_ID/embedded-just-for-fun.git
cd embedded-just-for-fun
git remote add upstream https://github.com/zinee-u/embedded-just-for-fun.git
git remote -v
```

- `origin`은 자기 Fork입니다.
- `upstream`은 `zinee-u/embedded-just-for-fun`입니다.
- `upstream`이 이미 등록돼 있으면 `git remote add`를 반복하지 말고 `git remote -v`로 주소를 확인합니다.

본인 Commit 작성자 정보를 설정합니다. 개인 이메일 대신 GitHub Settings → Emails에서 확인한 본인의 `noreply` 주소를 사용해도 됩니다.

```sh
git config --local user.name "YOUR_GITHUB_ID"
git config --local user.email "YOUR_COMMIT_EMAIL"
```

## 2. 최신 원본에서 4주차 Branch 만들기

현재 변경 사항을 먼저 확인하고 이전 과제 작업은 Commit하거나 별도로 보관하세요. 아래 명령은 **Clone한 저장소 루트**에서 실행합니다.

```sh
git status --short
git fetch upstream
git switch -c solve/week04-YOUR_GITHUB_ID upstream/main
```

새 Branch를 `upstream/main`에서 만들면 이전 주차 풀이가 섞이는 것을 피할 수 있습니다. 이미 4주차를 시작했다면 `git switch solve/week04-YOUR_GITHUB_ID`로 기존 Branch에 돌아가고, 다음 복사 명령으로 작성한 파일을 덮어쓰지 마세요.

## 3. 자기 제출 폴더에 starter 전체 복사하기

처음 시작하며 해당 제출 폴더가 없는 상태에서 다음 명령을 실행합니다.

```sh
mkdir -p submissions/week04/YOUR_GITHUB_ID
cp -R weeks/week04/starter/. submissions/week04/YOUR_GITHUB_ID/
cd submissions/week04/YOUR_GITHUB_ID
```

이제부터 편집하는 기준 경로는 이 폴더입니다. `weeks/week04/starter`를 직접 고치지 않습니다. 폴더 안에서 `git init`을 실행하지 않습니다.

## 4. 개발 도구 확인하고 C 구현하기

Host test에는 C11을 지원하는 C Compiler와 GNU Make가 필요합니다. macOS/Linux에서는 설치된 도구를, Windows에서는 [MSYS2 설치 안내](https://www.msys2.org/)와 [UCRT64 환경 안내](https://www.msys2.org/docs/environments/)를 참고해 GCC·Make를 함께 사용할 수 있는 환경을 준비합니다. Git Bash 자체에 Compiler·Make가 포함돼 있다고 가정하지 마세요.

```sh
cc --version
make --version
```

Compiler 이름이 `gcc`인 환경에서는 `make CC=gcc test`, `make CC=gcc stages`처럼 실제 이름을 지정할 수 있습니다. Windows 환경에서 실행 File 확장자가 필요하면 `make CC=gcc EXEEXT=.exe test`, `make CC=gcc EXEEXT=.exe stages`를 사용합니다. OS별 실행 File 형식이 다르므로 모든 Host 산출물이 ELF인 것은 아닙니다. 사용한 환경과 명령은 `BUILD_ENV.md`에 적습니다.

[개발 요청](README.md)에 따라 다음 File을 구현합니다.

- `src/memory_map.c`: 요구 주소 영역을 판정합니다.
- `src/clock.c`: Clock 요구값과 실패 전달을 구현합니다.
- `src/led.c`: LED 요구값과 초기화 순서를 구현합니다.
- `src/app.c`: 전체 초기화·실패 중단·반복 동작을 구현합니다.

제공된 API와 검증 코드를 바꾸지 않고, 자신의 추가 검증을 최소 2개 `tests/test_student.c`의 `run_student_tests`에 작성합니다. 같은 폴더의 `README.md`, `BUILD_ENV.md`, `TRACE.md`도 채웁니다.

## 5. Host test와 Build 단계를 실제 실행하고 Log 남기기

다음 명령은 계속 **자기 제출 폴더**에서 실행합니다. 구현 전에 실행하면 실패할 수 있습니다. 최종 제출 Log는 제출할 코드에서 다시 만든 실제 결과여야 합니다.

```sh
mkdir -p logs
make clean
make test > logs/test.log 2>&1
test_status=$?
printf '\nmake test exit code: %s\n' "$test_status" >> logs/test.log
cat logs/test.log
```

Exit code가 0인지 확인하고 실패한 검사와 Compiler 오류를 모두 해결합니다. `CC=gcc`가 필요한 환경은 위 `make test`를 `make CC=gcc test`로 바꿉니다.

```sh
make clean
make stages > logs/stages.log 2>&1
stages_status=$?
printf '\nmake stages exit code: %s\n' "$stages_status" >> logs/stages.log
cat logs/stages.log
```

`make stages`도 Exit code 0을 확인합니다. 앞의 `make clean`은 실제 Build 명령이 Log에 남도록 중간 산출물을 지우며, `logs/test.log`는 유지합니다. 생성된 `.i`, `.s`, `.o`, Host 실행 File을 살펴보고 `TRACE.md`에 단계별 역할을 적으세요. Host Compile과 실제 MCU의 ARM Build를 구분합니다.

테스트 실패를 숨기거나 Log를 성공 결과로 고쳐 적지 않습니다. 코드 수정 뒤에는 필요한 명령을 다시 실행해 Log를 갱신합니다. 생성 산출물 `build/`는 Commit하지 않으며, 검토용 `logs/test.log`, `logs/stages.log`는 Commit합니다.

## 6. 목적이 다른 Commit을 2개 이상 남기기

자기 제출 폴더에서 저장소 루트로 돌아갑니다.

```sh
cd ../../..
git status --short
git diff -- submissions/week04/YOUR_GITHUB_ID
git add submissions/week04/YOUR_GITHUB_ID/src \
  submissions/week04/YOUR_GITHUB_ID/include \
  submissions/week04/YOUR_GITHUB_ID/host \
  submissions/week04/YOUR_GITHUB_ID/tests \
  submissions/week04/YOUR_GITHUB_ID/Makefile \
  submissions/week04/YOUR_GITHUB_ID/.gitignore
git commit -m "Implement week04 MCU initialization modules"
```

첫 Commit은 본인이 작성한 구현·추가 테스트와 실행에 필요한 제공 API·Host 대역·Makefile을 함께 담습니다. 해당 Commit만 받아도 검증할 수 있게 구성합니다. 이어서 근거·환경 설명과 실제 실행 Log를 두 번째 Commit에 담습니다.

```sh
git add submissions/week04/YOUR_GITHUB_ID
git diff --cached --stat
git diff --cached
git commit -m "Verify week04 requirements and record build environment"
git log --oneline --stat -2
git show --stat HEAD
```

두 Commit의 목적과 실제 SHA를 PR 본문에 적습니다. 빈 Commit을 만들어 개수만 채우지 않습니다. `git diff --cached`에 자기 폴더 밖의 파일이나 `build/`가 보이면 Commit 전에 원인을 확인하세요.

## 7. 자기 Fork에 Push하기

```sh
git push -u origin solve/week04-YOUR_GITHUB_ID
```

GitHub 인증이 필요하면 본인 계정으로 진행합니다. Token을 소스나 문서에 저장하지 않습니다.

## 8. 원본 저장소에 Pull Request 만들기

1. GitHub에서 자신의 Fork를 열고 **Compare & pull request**를 누릅니다. 안내가 없다면 **Pull requests → New pull request**에서 비교 Branch를 고릅니다.
2. **base repository:** `zinee-u/embedded-just-for-fun`
3. **base:** `main`
4. **head repository:** `YOUR_GITHUB_ID/embedded-just-for-fun`
5. **compare:** `solve/week04-YOUR_GITHUB_ID`
6. **제목:** `[week04] YOUR_GITHUB_ID MCU 초기화 기능 구현`
7. 자동 입력된 공용 양식 대신 [4주차 PR 본문](PR_BODY.md)을 복사해 실제 결과로 채웁니다.
8. **Files changed**에서 자기 `submissions/week04/YOUR_GITHUB_ID/`만 변경됐는지 확인합니다.
9. 검토 준비가 됐다면 **Create pull request**를 누릅니다. 진행 중이면 Draft로 열고 완료 후 검토 가능한 상태로 전환합니다.

자기 Fork 내부 `main`을 대상으로 열린 PR은 이 과제 제출 대상과 다릅니다. PR 상단의 base 저장소 이름을 확인하고, 제출한 실제 PR 링크를 보관하세요.

## 9. Review 의견에 답하고 같은 PR에 반영하기

검토 의견을 받으면 같은 Branch에서 자기 제출 파일을 고칩니다. 영향받는 test를 다시 실행하고 Log·문서를 갱신합니다.

```sh
git add submissions/week04/YOUR_GITHUB_ID
git diff --cached
git commit -m "Address week04 review feedback"
git push
```

새 PR을 만들지 않아도 기존 PR에 Commit이 추가됩니다. 의견에는 “수정했습니다”만 적기보다 **원인, 변경한 File, 확인한 test 결과**로 답해 주세요. 검토 후 병합 여부는 스누피가 결정합니다.

## 제출 전 마지막 확인

- 네 `.c` File에 제품 요구값과 동작이 반영돼 있습니다.
- 제공 API·검증 기준을 우회하지 않고 추가 테스트를 작성했습니다.
- `make test`, `make stages`가 성공했으며 최종 코드의 실제 Log를 첨부했습니다.
- Datasheet·공개 Build·Startup 근거와 Host 검증 한계를 설명했습니다.
- 본인이 작성한 목적별 Commit이 최소 2개 있습니다.
- PR은 원본 저장소 `main`을 대상으로 자기 제출 폴더만 변경합니다.
