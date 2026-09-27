# Pull Request로 과제 제출하기

과제 원본은 그대로 두고 자기 폴더에 개선안을 제출합니다. 다른 학생과 파일이 겹치지 않아 각 PR을 독립적으로 검토하고 병합할 수 있습니다.

## 1 처음 한 번 준비하기

GitHub 계정과 Git, C 컴파일러를 준비합니다. Windows에서는 Git Bash에서 아래 명령을 사용할 수 있습니다. 컴파일러는 별도로 설치되어 있어야 합니다.

이 저장소 우측 상단의 **Fork**로 자기 계정에 복사합니다. 아래의 `YOUR_GITHUB_ID`는 모두 자신의 GitHub 아이디로 바꾸세요.

```sh
git clone https://github.com/YOUR_GITHUB_ID/embedded-just-for-fun.git
cd embedded-just-for-fun
git remote add upstream https://github.com/zinee-u/embedded-just-for-fun.git
```

커밋 이름과 이메일은 자기 정보로 설정합니다. 개인 이메일 공개가 싫다면 GitHub Settings의 Emails에서 확인한 본인 `noreply` 주소를 사용할 수 있습니다.

```sh
git config --local user.name "YOUR_GITHUB_ID"
git config --local user.email "YOUR_COMMIT_EMAIL"
```

## 2 최신 과제에서 새 브랜치 만들기

작업 중인 변경을 먼저 커밋하거나 별도로 보관한 뒤 진행하세요. 새 주차를 시작할 때마다 `upstream/main`에서 브랜치를 만들면 이전 풀이가 새 PR에 섞이지 않습니다.

```sh
git fetch upstream
git switch -c solve/week02-YOUR_GITHUB_ID upstream/main
mkdir -p submissions/week02/YOUR_GITHUB_ID
cp weeks/week02/starter/decode_rain.c submissions/week02/YOUR_GITHUB_ID/decode_rain.c
cp templates/submission/README.md submissions/week02/YOUR_GITHUB_ID/README.md
```

이미 같은 주차에 PR을 만들었다면 새 브랜치를 만들지 말고 기존 PR의 브랜치로 돌아가 수정합니다. 제출 폴더가 이미 존재하면 기존 파일을 덮어 복사하지 말고 해당 파일을 이어서 수정하세요.

## 3 원인을 찾고 구현하기

[2주차 문제](weeks/week02/README.md)의 조건을 기준으로 코드를 수정합니다. 함수 매개변수와 반환형을 바꿀 수 있으며 특정 정답 API를 강제하지 않습니다. 자신의 API에 맞는 `tests.c`도 같은 폴더에 작성하세요.

- `decode_rain.c`: 개선한 구현. 파일을 추가로 나누어도 됩니다.
- `tests.c`: 정상·경계·오류 입력과 호출자 동작을 검사하는 실행 가능한 테스트.
- `README.md`: 발견한 모든 근본 원인, 수정 근거, 선택의 단점, 빌드 명령, 실제 실행 결과.

`cases.csv`는 요구 조건을 확인하는 시작점입니다. 인터페이스가 자유로우므로 특정 함수 시그니처를 요구하는 자동 채점기는 제공하지 않습니다. 자신의 설계에서 생기는 조건도 테스트에 추가하세요.

구현에 `main`이 없고 `tests.c`에 테스트용 `main`이 있다면 다음처럼 빌드할 수 있습니다. 헤더나 소스 파일을 추가했다면 명령도 맞게 고쳐 README에 남깁니다. `tests.c`에서 `.c` 파일을 직접 include한 뒤 같은 `.c`를 또 컴파일하지 마세요.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -fsigned-char \
  submissions/week02/YOUR_GITHUB_ID/decode_rain.c \
  submissions/week02/YOUR_GITHUB_ID/tests.c \
  -o /tmp/week02-test
/tmp/week02-test
```

위 명령은 GCC/Clang 계열의 호스트 실행 예입니다. 이 저장소에서는 C11 기준의 설명을 권장하지만 원문이 특정 C 버전을 지정한 것은 아닙니다. 다른 환경을 쓰면 버전과 옵션을 적으세요. 일반 PC의 데이터 포인터는 8바이트일 수 있으므로 호스트 테스트를 32-bit MCU 검증으로 표시하지 않습니다.

## 4 자신의 파일만 커밋하고 푸시하기

```sh
git status --short
git diff
git add submissions/week02/YOUR_GITHUB_ID
git commit -m "Solve week02 wiper sensor decoding"
git push -u origin solve/week02-YOUR_GITHUB_ID
```

`weeks`, `templates`, 다른 학생 폴더는 풀이 PR에서 수정하지 않습니다. 문제 자체의 오탈자나 조건 오류를 발견했다면 풀이와 분리한 문서 수정 PR로 알려 주세요.

## 5 PR 열기

1. GitHub에서 자신의 Fork로 이동해 **Compare & pull request**를 누릅니다.
2. **base repository**는 `zinee-u/embedded-just-for-fun`, **base**는 `main`인지 확인합니다.
3. **head repository**는 자신의 Fork, **compare**는 `solve/week02-YOUR_GITHUB_ID`를 선택합니다.
4. 제목을 `[week02] YOUR_GITHUB_ID 와이퍼 센서값 변환 개선`으로 적고 PR 양식을 채웁니다.
5. **Files changed**에서 자기 제출 폴더만 포함됐는지 확인한 뒤 **Create pull request**를 누릅니다. 진행 중이라면 Draft PR로 시작해도 됩니다.

검토 의견을 받으면 같은 브랜치를 수정하고 커밋·푸시하세요. 기존 PR에 자동으로 추가됩니다. 검토가 끝나면 출제자가 병합 여부를 결정합니다. 한 PR에는 한 주차의 풀이만 담으세요.

## 다음 주차

`git fetch upstream`으로 새 과제를 받고, `upstream/main`에서 `solve/week03-YOUR_GITHUB_ID`와 같은 새 브랜치를 만듭니다. 제출 경로의 `week02`도 해당 주차로 바꿉니다. 새 주차 추가는 [매주 관리 안내](docs/WEEKLY_MAINTENANCE.md)에 설명되어 있습니다.
