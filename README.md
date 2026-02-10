# cpp-windows-socket-client

개인용 C++ **Windows TCP 클라이언트** 소켓 코드/라이브러리. (WinSock)  
**친절한 설명 없음.** 불편하면 쓰지 말고, 쓸 거면 **코드부터** 봐라.

- 목적: 내가 쓰려고 만든 것
- 상태: 필요한 만큼만 유지보수
- 보증: 없음 (진짜로 없음)

---

## What this is

- Windows 환경 **TCP 클라이언트 소켓(WinSock)** 구현
- “재사용 가능한 코드”처럼 보이지만, 기본적으로 **내 프로젝트 부품**

---

## Where to look

- `include/` : 헤더 (외부에 보여줄 의도)
- `src/` : 구현 (진짜 내용)
- `examples/` : 있으면 참고, 없으면 알아서 읽어라

---

## Build (CMake)

```bash
git clone https://github.com/ryoma-core/cpp-windows-socket-client
cd cpp-windows-socket-client/Socket

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
