import fs from "fs";
import { getAllSkins, getDefaultSkin } from "./parser";
import { ItemDefinitionIndex } from "../src/utils/weapon";

const weaponsUrls = [
  //PISTOLS
  "https://csgostash.com/weapon/USP-S",
  "https://csgostash.com/weapon/Tec-9",
  "https://csgostash.com/weapon/R8+Revolver",
  "https://csgostash.com/weapon/P250",
  "https://csgostash.com/weapon/P2000",
  "https://csgostash.com/weapon/Glock-18",
  "https://csgostash.com/weapon/Five-SeveN",
  "https://csgostash.com/weapon/Dual+Berettas",
  "https://csgostash.com/weapon/Desert+Eagle",
  "https://csgostash.com/weapon/CZ75-Auto",
  ///RIFLES
  "https://csgostash.com/weapon/AK-47",
  "https://csgostash.com/weapon/AUG",
  "https://csgostash.com/weapon/AWP",
  "https://csgostash.com/weapon/FAMAS",
  "https://csgostash.com/weapon/G3SG1",
  "https://csgostash.com/weapon/Galil+AR",
  "https://csgostash.com/weapon/M4A1-S",
  "https://csgostash.com/weapon/M4A4",
  "https://csgostash.com/weapon/SCAR-20",
  "https://csgostash.com/weapon/SG+553",
  "https://csgostash.com/weapon/SSG+08",
  //SMGS
  "https://csgostash.com/weapon/MAC-10",
  "https://csgostash.com/weapon/MP5-SD",
  "https://csgostash.com/weapon/MP7",
  "https://csgostash.com/weapon/MP9",
  "https://csgostash.com/weapon/PP-Bizon",
  "https://csgostash.com/weapon/P90",
  "https://csgostash.com/weapon/UMP-45",
  //HEAVIES
  "https://csgostash.com/weapon/MAG-7",
  "https://csgostash.com/weapon/Nova",
  "https://csgostash.com/weapon/Sawed-Off",
  "https://csgostash.com/weapon/XM1014",
  "https://csgostash.com/weapon/M249",
  "https://csgostash.com/weapon/Negev",
  //KNIVES
  "https://csgostash.com/weapon/Nomad+Knife",
  "https://csgostash.com/weapon/Skeleton+Knife",
  "https://csgostash.com/weapon/Survival+Knife",
  "https://csgostash.com/weapon/Paracord+Knife",
  "https://csgostash.com/weapon/Classic+Knife",
  "https://csgostash.com/weapon/Bayonet",
  "https://csgostash.com/weapon/Bowie+Knife",
  "https://csgostash.com/weapon/Butterfly+Knife",
  "https://csgostash.com/weapon/Falchion+Knife",
  "https://csgostash.com/weapon/Flip+Knife",
  "https://csgostash.com/weapon/Gut+Knife",
  "https://csgostash.com/weapon/Huntsman+Knife",
  "https://csgostash.com/weapon/Karambit",
  "https://csgostash.com/weapon/M9+Bayonet",
  "https://csgostash.com/weapon/Navaja+Knife",
  "https://csgostash.com/weapon/Shadow+Daggers",
  "https://csgostash.com/weapon/Stiletto+Knife",
  "https://csgostash.com/weapon/Talon+Knife",
  "https://csgostash.com/weapon/Ursus+Knife",
];

async function main() {
  const defaultSkins: { [T in ItemDefinitionIndex | string]?: string } = {};

  const writeStream = fs.createWriteStream("skins.json");
  writeStream.write("{", "utf8");
  writeStream.write(`"skins": [`, "utf8");

  for (let i = 0; i < weaponsUrls.length; i++) {
    console.log(`[MAIN]: Parse [${i}/${weaponsUrls.length}]`);

    const data = await getAllSkins(weaponsUrls[i]);
    if (!data) {
      continue;
    }

    const defaultSkin = await getDefaultSkin(weaponsUrls[i]);
    if (defaultSkin) {
      defaultSkins[data[0].weapon] = defaultSkin;
      defaultSkins[data[0].weaponDI] = defaultSkin;
    }

    data.forEach((d, j) => {
      if (d.paintKit <= 0) {
        return;
      }
      writeStream.write(JSON.stringify(d), "utf8");
      if (j !== data.length - 1) {
        writeStream.write(",", "utf8");
      }
    });

    if (i !== weaponsUrls.length - 1) {
      writeStream.write(",", "utf8");
    }
  }

  writeStream.write("],", "utf8");
  writeStream.write(`"default":`, "utf8");
  writeStream.write(JSON.stringify(defaultSkins), "utf8");
  writeStream.write("}", "utf8");
  writeStream.end();
  return 0;
}

main();
