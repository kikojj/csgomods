import { makeStyles } from "@material-ui/styles";
import { colors, getColumnWidth } from "@utils";

const COLS = 2;
export const useStyles = makeStyles({
  global: {
    float: "left",
    width: getColumnWidth(COLS, 100),
  },
  weapon: {
    float: "left",
    marginLeft: 100,
    width: getColumnWidth(COLS, 100),
  },
});
