import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  container: {
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
  exit: {
    margin: "0 30px",
  },
});
