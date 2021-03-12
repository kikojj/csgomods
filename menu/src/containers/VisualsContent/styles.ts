import { makeStyles } from "@material-ui/styles";
import { colors, getColumnWidth } from "@utils";

const COLS = 2;
export const useStyles = makeStyles({
  glowEsp: {
    float: "left",
    width: getColumnWidth(COLS),
  },
  chams: {
    float: "left",
    marginLeft: 100,
    width: getColumnWidth(COLS),
  },
});
