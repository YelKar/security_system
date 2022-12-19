const char page[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
</head>
<body>
    <button class="alert">АХТУНГ</button>
    <button class="cancel">ОТМЕНА</button>
    <div class="text">qwerty</div>
</body>
<script>
    let alert = document.querySelector(".alert");
    let cancel = document.querySelector(".cancel");
    let text = document.querySelector(".text");
    alert.addEventListener(
        "click",
        async () => {
            await fetch("/alert");
        }
    );
    cancel.addEventListener(
        "click",
        async () => {
            await fetch("/cancel");
        }
    );
    document.addEventListener(
      "keydown", 
        async (e) => {
            if (e.code == "KeyC") {
              await fetch("/cancel");
            }
            if (e.code == "KeyV") {
              await fetch("/alert");
            }
        }
    );
    setInterval(async () => {
      let res = await fetch("/update");
      text.textContent = `${(await res.json()).btn}`;
    }, 100);
</script>
</html>
)rawliteral";