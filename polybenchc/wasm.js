const fs = require("fs");

WebAssembly.instantiate(fs.readFileSync("out.wasm"), {}).then(mod => {
    mod.instance.exports.main();
})