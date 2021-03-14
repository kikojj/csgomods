import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  container: {
    display: "flex",
  },
  items_containers: {
    display: "grid",
    gridTemplateColumns: "133px 133px 133px 133px",
    gridColumnGap: 12,
    gridAutoRows: 160,
    gridRowGap: 12,
  },
  title_back: {
    display: "flex",
    alignItems: "center",

    "& > img": {
      display: "block",
      marginRight: 10,
      cursor: "pointer",
    },
  },
});
