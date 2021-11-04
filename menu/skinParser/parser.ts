import request from "request";
import cheerio from "cheerio";
import { TSkin, SKIN, getRarity, skinRaritiesText, Weapon } from "../src/utils";

function isTag(e: cheerio.Element): e is cheerio.TagElement {
  if ((e as any).type === "tag") {
    return true;
  }
  return false;
}

function isText(e: cheerio.Element): e is cheerio.TextElement {
  if ((e as any).type === "text") {
    return true;
  }
  return false;
}

export const getAllSkinForWeapon = (weaponUrl: string) => {
  return new Promise<string[] | undefined>((resolve, reject) => {
    const res: string[] = [];

    request(weaponUrl, (error: any, _: any, body: any) => {
      if (body) {
        const $ = cheerio.load(body);

        const itemsImages = $(".result-box img");
        itemsImages.each((i, img) => {
          if (isTag(img)) {
            if (img.parent && isTag(img.parent)) {
              const a = img.parent;
              const url = a.attribs.href;
              if (url && url.includes("/skin/")) {
                res.push(url);
              }
            }
          }
        });
        resolve(res);
      } else {
        resolve(undefined);
      }
    });
  });
};

export const getSkin = (skinUrl: string) => {
  return new Promise<TSkin[] | undefined>((resolve, reject) => {
    const skin: TSkin = { ...SKIN, collections: [], collectionsImage: [] };

    const variants: { paintKits: number[]; images: string[] } = { paintKits: [], images: [] };

    request(skinUrl, (error: any, _: any, body: any) => {
      if (body) {
        const $ = cheerio.load(body);

        const resultBox = $(".result-box");
        const title = resultBox.find("h2 > a");

        if (isTag(title[0])) {
          const children = title[0].children;
          if (isText(children[0])) {
            skin.weapon = children[0].data || "";
          }
        }
        if (isTag(title[1])) {
          const children = title[1].children;
          if (isText(children[0])) {
            skin.name = children[0].data || "";
          }
        }

        if (skin.weapon) {
          const weapon = new Weapon({ name: skin.weapon });
          skin.weaponDI = weapon.itemDI;
        }

        const rarityTag = resultBox.find(".quality > p");
        if (rarityTag[0] && isTag(rarityTag[0])) {
          if (isText(rarityTag[0].children[0]) && rarityTag[0].children[0].data) {
            const rarity = rarityTag[0].children[0].data;
            skin.rarityID = getRarity(rarity);
            skin.rarity = skinRaritiesText[skin.rarityID];
          }
        }

        const mainImage = resultBox.find("img.main-skin-img");
        if (mainImage && mainImage.attr("src")) {
          skin.image = mainImage.attr("src")!;
        }

        let collectionsImage = $(".skin-details-multiple-container-wrapper img");
        if (collectionsImage.length == 0) {
          collectionsImage = $(".skin-details-collection-container-wrapper img");
        }

        collectionsImage.each((i, c) => {
          if (isTag(c)) {
            if (c.attribs.src && c.attribs.alt) {
              skin.collections.push(c.attribs.alt);
              skin.collectionsImage.push(c.attribs.src.split("?")[0]);
            }
          }
        });

        const skinDetails = $(".skin-misc-details > p > strong");
        skinDetails.each((i, d) => {
          if (isTag(d)) {
            if (isText(d.children[0]) && d.children[0].data?.includes("Finish Catalog")) {
              if (d.next && d.next.next && isTag(d.next.next)) {
                const paintKitTag = d.next.next;
                if (isText(paintKitTag.children[0])) {
                  if (paintKitTag.children[0].data) {
                    const paintKit = paintKitTag.children[0].data;

                    if (!paintKit.toLowerCase().includes("multiple")) {
                      skin.paintKit = parseInt(paintKit);
                    } else {
                      const paintKitEl = $("#preview-variants div > p > em");

                      paintKitEl.each((i, el) => {
                        if (el && isTag(el) && el.children && el.children[0] && isText(el.children[0])) {
                          const paintKit = el.children[0].data;
                          if (paintKit) {
                            variants.paintKits.push(parseInt(paintKit.split("#")[1]));
                          }
                        }
                      });

                      const imageEl = $("#preview-variants a > img");
                      imageEl.each((i, el) => {
                        if (el && isTag(el) && el.attribs && el.attribs.src) {
                          variants.images.push(el.attribs.src);
                        }
                      });
                    }
                  }
                }
              }
            }
            if (isText(d.children[0]) && d.children[0].data?.includes("Description")) {
              if (d.next && isText(d.next)) {
                if (d.next.data) {
                  const desc = d.next.data;
                  skin.description = desc.slice(0, desc.length - 1);
                }
              }
            }
          }
        });

        if (variants.paintKits.length === 0) {
          resolve([skin]);
        } else {
          const skins: TSkin[] = [];
          variants.paintKits.map((paintKit, i) => {
            skins.push({ ...skin, paintKit, image: variants.images[i] });
          });
          resolve(skins);
        }
      } else {
        resolve(undefined);
      }
    });
  });
};

export const getAllSkins = async (weaponUrl: string) => {
  // console.log(`[PARSER]: Started.`);
  const result: TSkin[] = [];

  // console.log(`[PARSER]: Getting all skin's urls.`);
  const skinsUrls = await getAllSkinForWeapon(weaponUrl);
  // console.log(`[PARSER]: Got.`);
  if (!skinsUrls) {
    return undefined;
  }
  for (let i in skinsUrls) {
    const skin = await getSkin(skinsUrls[i]);
    if (skin) {
      result.push(...skin);
      // console.log(`[PARSER]: Parsing... [${i}/${skinsUrls.length}]`);
    }
  }
  return result;
};

export const getDefaultSkin = async (weaponUrl: string) => {
  return new Promise<string | undefined>((resolve, reject) => {
    request(weaponUrl, (error: any, _: any, body: any) => {
      if (body) {
        const $ = cheerio.load(body);

        const skinsImages = $(".result-box img");
        skinsImages.each((i, img) => {
          if (isTag(img) && img.attribs) {
            if (
              img.attribs.src &&
              img.attribs.alt &&
              (img.attribs.alt.includes("Default") || img.attribs.alt.includes("Vanilla"))
            ) {
              resolve(img.attribs.src.split("?")[0]);
            }
          }
        });
      } else {
        resolve(undefined);
      }
    });
  });
};
