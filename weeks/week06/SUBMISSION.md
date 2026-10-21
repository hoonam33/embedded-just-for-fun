# 06회차 과제를 Pull Request로 제출하기

명령은 Git Bash 또는 macOS/Linux Terminal 기준입니다. `YOUR_GITHUB_ID`와 `YOUR_COMMIT_EMAIL`을 본인의 정보로 바꿉니다. [풀이 접근법](APPROACH.md)을 참고한 뒤 원본 Starter를 자기 제출 폴더에 복사해 직접 개선합니다. 아래 순서로 자신의 Fork에서 작업하고 원본 저장소에 PR을 제출합니다.

## 1. Fork와 Clone

원본 저장소 https://github.com/zinee-u/embedded-just-for-fun 에서 자신의 Fork를 만든 뒤 Clone합니다. 이미 준비한 Clone이 있으면 다시 만들지 않습니다.

```sh
git clone https://github.com/YOUR_GITHUB_ID/embedded-just-for-fun.git
cd embedded-just-for-fun
git remote add upstream https://github.com/zinee-u/embedded-just-for-fun.git
git remote -v
git config --local user.name "YOUR_GITHUB_ID"
git config --local user.email "YOUR_COMMIT_EMAIL"
```

`upstream`이 이미 있으면 추가 명령을 반복하지 말고 주소만 확인합니다. `origin`은 자신의 Fork여야 합니다.

## 2. Branch와 자기 제출 폴더

기존 작업은 먼저 Commit하거나 별도로 보관하고 상태를 확인합니다. 아래 복사 명령은 새 풀이를 시작할 때만 실행합니다. 이미 작성한 코드를 덮어쓰지 않습니다.

```sh
git status --short
git fetch upstream
git switch -c solve/week06-YOUR_GITHUB_ID upstream/main
mkdir -p submissions/week06/YOUR_GITHUB_ID
cp -R weeks/week06/starter/. submissions/week06/YOUR_GITHUB_ID/
cd submissions/week06/YOUR_GITHUB_ID
```

제출 폴더 안에서 `git init`을 다시 실행하지 않습니다.

## 3. 환경과 원본 실패 기록

C11 Compiler와 GNU Make가 필요합니다. Windows에서는 GCC·Make가 설치된 MSYS2 UCRT64 같은 환경을 사용할 수 있습니다. Git Bash에 Compiler가 기본 포함됐다고 가정하지 않습니다. 실제 GCC를 사용한다면 `make CC=gcc test`처럼 지정합니다.

```sh
cc --version
make --version
mkdir -p logs
make clean
make test > logs/before-test.log 2>&1
before_status=$?
printf '\nmake test exit code: %s\n' "$before_status" >> logs/before-test.log
cat logs/before-test.log
```

원본은 의도적인 결함이 있어 실패합니다. 이 Log를 보존한 뒤 수정합니다. 실행 전 기대값과 실제 결과를 구분합니다.

## 4. 코드·분석·추가 Test

세 `src/*.c`를 개선하고 `tests/test_student.c`에 서로 다른 경계 Test를 최소 2개 추가합니다. `README.md`, `CONCURRENCY.md`, `BUILD_ENV.md`도 채웁니다. 제공 API·Host·고정 Test·관찰 Hook의 계약을 바꾸지 않습니다. private Helper는 추가할 수 있습니다.

Polling과 Interrupt의 흐름도, 읽기·초기화 사이의 Race timeline, 이전 IRQ 상태 복구, Sensor/Publish 중 다음 요청의 보존을 설명합니다. 모든 근본 원인을 요구 조건·증거·Test에 연결합니다.

## 5. 최종 실행 결과 저장

```sh
make clean
make test > logs/test.log 2>&1
test_status=$?
printf '\nmake test exit code: %s\n' "$test_status" >> logs/test.log
cat logs/test.log
```

실패하면 원인을 수정한 뒤 최종 코드로 다시 기록합니다. Demo도 먼저 Build와 실행 성공을 확인한 뒤 CSV를 저장합니다.

```sh
make demo
make -s demo > logs/demo.csv
```

최종 Test와 Demo의 Exit code가 0이어야 합니다. `-s`는 Make 명령 표시를 숨기는 옵션입니다. 가상 Tick과 Hook 결과를 TC387QP 지연 측정으로 쓰지 않습니다.

## 6. 변경을 확인하고 자신의 Fork에 Push

제출 폴더에서 저장소 루트로 돌아갑니다. 구현과 검증·설명처럼 목적이 다른 변경을 Commit으로 남깁니다. 개수만 맞춘 빈 Commit은 만들지 않습니다.

```sh
cd ../../..
git add submissions/week06/YOUR_GITHUB_ID/src \
  submissions/week06/YOUR_GITHUB_ID/include \
  submissions/week06/YOUR_GITHUB_ID/host \
  submissions/week06/YOUR_GITHUB_ID/tests \
  submissions/week06/YOUR_GITHUB_ID/Makefile \
  submissions/week06/YOUR_GITHUB_ID/.gitignore
git diff --cached
git commit -m "Implement week06 interrupt collector"
git add submissions/week06/YOUR_GITHUB_ID
git diff --cached
git commit -m "Verify week06 concurrency and document evidence"
git push -u origin solve/week06-YOUR_GITHUB_ID
```

`build/`, SDK 전체, 인증 파일은 포함하지 않습니다. `logs/*.log`와 `logs/demo.csv`가 실제 포함됐는지 확인합니다.

## 7. 원본 저장소로 PR

- Base repository: `zinee-u/embedded-just-for-fun`
- Base branch: `main`
- Head repository: 자신의 Fork
- Compare branch: `solve/week06-YOUR_GITHUB_ID`
- 제목: `[06회차] YOUR_GITHUB_ID TC387QP Interrupt 수집 개선`

[PR 본문](PR_BODY.md)을 실제 결과로 채웁니다. Files changed에는 자기 제출 폴더만 보여야 합니다. 자신의 Fork 내부 PR만 만들면 원본 저장소에 제출된 것이 아닙니다. Review에 따른 수정은 같은 Branch에 Commit하고 Push합니다.
