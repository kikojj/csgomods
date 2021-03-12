const express = require("express");

const app = express();

const PORT = process.argv.find((s) => s.includes("port"))?.split("=")[1] || 2223;
const DIRECTORY = process.argv.find((s) => s.includes("dir"))?.split("=")[1] || "dist";

app.use(express.static(DIRECTORY));

app.listen(PORT, () => {
  console.log(`[Node http server]: Started on port ${PORT}.`);
});
