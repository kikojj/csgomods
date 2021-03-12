import { makeStyles } from "@material-ui/styles";
import { colors_ as colors, hexAlpha } from "@utils";

export default makeStyles({
  selectItem: {
    padding: "7px 10px",
    display: "block",
    width: "100%",

    backgroundColor: colors.darkBlue,

    fontSize: 14,
    color: "#fff",
    textAlign: "left",

    cursor: "pointer",

    transition: "0.2s background-color ease",

    "&:hover": {
      backgroundColor: colors.teritary,
    },
  },
});
