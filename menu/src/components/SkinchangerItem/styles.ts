import { makeStyles } from "@material-ui/styles";
import { colors, SkinRarity, rarityColors } from "@utils";

type Props = {
  rarity: SkinRarity;
  active: boolean;
  url: string;
};
export const useStyles = makeStyles({
  background: {
    padding: 2,
    width: 133,
    height: 160,

    background: (props: Props) => `linear-gradient(180deg, ${colors.blue2} 0%, ${rarityColors[props.rarity]} 100%)`,
    borderRadius: 5,

    cursor: "pointer",

    transition: "0.3s background ease",

    position: "relative",

    "&:hover": {
      background: `linear-gradient(180deg, ${colors.blue2} 0%, #fff 100%)`,
    },

    "&:after": {
      width: 12,
      height: 12,
      display: (props: Props) => (props.active ? "block" : "none"),

      backgroundColor: "#fff",
      borderRadius: 6,
      content: "''",

      position: "absolute",
      top: 8,
      left: 8,
    },
  },
  content: {
    padding: 10,
    height: 156,

    display: "flex",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",

    backgroundColor: colors.dark,
    borderRadius: 5,
  },
  image: {
    width: 100,
    height: 100,

    backgroundImage: (props: Props) => `url(${props.url})`,
    backgroundSize: 'contain',
    backgroundRepeat: 'no-repeat',
    backgroundPosition: 'center'
  },
  name: {
    marginTop: 15,

    fontSize: 14,
    fontWeight: 400,
    color: "#fff",
    textAlign: "center",
  },
});
