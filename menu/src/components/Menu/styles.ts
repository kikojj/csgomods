import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  contanier: {
    padding: "30px 0",
    height: "100%",

    background: `linear-gradient(180deg, ${colors.blue2} 0%, ${colors.teritary} 100%)`,

    overflowY: "auto",
    position: "fixed",
    left: 0,
    top: 0,
  },
  logo: {
    margin: "0 auto",
  },
  tabs: {
    marginTop: 20,
    width: "100%",
  },
  tab: {
    padding: "20px 30px",
    width: 250,

    position: "relative",
    cursor: "pointer",

    transition: "0.3s background-color ease",

    "&:hover > $tab_bg": {
      background: `linear-gradient(90deg, ${hexAlpha(colors.primary, 0)} 0%, ${hexAlpha(colors.primary, 5)} 100%)`,
    },

    "&-active  > $tab_bg": {
      background: `linear-gradient(90deg, ${hexAlpha(colors.primary, 0)} 0%, ${hexAlpha(colors.primary, 10)} 100%)`,
    },
  },
  tab_bg: {
    width: "calc(100% - 30px)",
    height: "100%",

    position: "absolute",
    top: 0,
    right: 0,
  },
  tab_content: {
    display: "flex",
    justifyContent: "space-between",
  },
  tab_content_text: {
    flex: 1,
  },
  tab_content_text_title: {
    fontWeight: 500,
    fontSize: 14,
    color: "#fff",
  },
  tab_content_text_subtitle: {
    marginTop: 5,
    fontWeight: 400,
    fontSize: 12,
    color: "rgba(255,255,255,0.6)",
  },
  tab_content_icon: {},
});
