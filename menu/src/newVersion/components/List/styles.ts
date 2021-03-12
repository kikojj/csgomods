import { makeStyles } from "@material-ui/styles";
import { colors_ as colors, hexAlpha } from "@utils";

export type Props = {
  color: string;
};
export const useStyles = makeStyles({
  container: {},
  item: {
    padding: 10,
    backgroundColor: colors.darkBlue,

    fontSize: 14,
    color: "#fff",

    cursor: "pointer",

    transition: "0.2s background ease",

    "&:first-of-type": {
      borderRadius: "2px 2px 0 0",
    },

    "&:last-of-type": {
      borderRadius: "0 0 2px 2px",
    },

    "&:hover": {
      backgroundColor: hexAlpha(colors.darkBlue, 50),
    },

    "&-selected": {
      backgroundColor: hexAlpha(colors.primary, 25),
    },
  },
});
