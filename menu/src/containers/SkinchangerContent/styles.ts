import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  content: {
    marginTop: 20,

    "&-btn": {
      display: "flex",
      alignItems: "flex-start",
      justifyContent: "space-between",

      "& $cards": {
        margin: "0",
      },
    },
  },
  cards: {
    margin: "0 auto",
    width: 860,
    display: "grid",
    gridTemplateColumns: "200px 200px 200px 200px",
    gridAutoRows: 210,
    gridColumnGap: 20,
    gridRowGap: 20,
  },
  btn_back: {
    marginBottom: 30,
  },
  skin_view_main: {
    display: "flex",
    justifyContent: "space-between",
  },
  skin_view_main_skin: {
    marginRight: 15,
  },
  skin_view_main_props: {
    padding: 20,
    flex: 1,
  },
  skin_view_info: {
    marginTop: 20,
  },
  skin_view_info_collection: {
    marginRight: 20,

    width: 150,
    height: 200,

    display: "flex",
    flexDirection: "column",
    alignItems: "center",
    justifyContent: "center",

    "&>img": {
      maxWidth: 100,
      maxHeight: 100,
    },
  },
  skin_view_main_props_apply: {
    marginTop: 20,
  },
});
