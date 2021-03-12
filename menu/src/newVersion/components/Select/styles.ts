import { makeStyles } from "@material-ui/styles";
import { colors_ as colors, hexAlpha } from "@utils";

export default makeStyles({
  selectContainer: {
    paddingTop: 7,
    width: "100%",
    position: "relative",
  },
  select: {
    padding: "7px 10px",
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",

    backgroundColor: hexAlpha(colors.primary, 5),
    borderRadius: 2,

    cursor: "pointer",
  },
  placeholder: {
    fontSize: 14,
    color: "#fff",

    transform: "translate(0, 0px) scale(1)",
    transformOrigin: "top left",
    transition: "transform 200ms cubic-bezier(0, 0, 0.2, 1) 0ms",

    position: "absolute",
    top: 14,
    left: 10,

    "&-value": {
      transform: "translate(0, -14px) scale(0.8)",
    },
  },
  selectItemList: {
    padding: "2px 0",
    width: 200,
    maxHeight: 300,

    borderRadius: "0px 0px 2px 2px",
    backgroundColor: colors.darkBlue,
    boxShadow: "0px 2px 2px rgba(0, 0, 0, 0.25)",

    overflowY: "auto",

    position: "absolute",
    top: 36,
    right: 0,
    zIndex: 1,

    // "&::-webkit-scrollbar": {
    //   width: "4px",
    // },

    // "&::-webkit-scrollbar-track": {
    //   WebkitBoxShadow: `inset 0 0 6px ${colors.blue2}`,
    //   borderRadius: "2px",
    // },

    // "&::-webkit-scrollbar-thumb": {
    //   borderRadius: "2px",
    //   WebkitBoxShadow: `inset 0 0 6px ${colors.primary}`,
    // },
  },
  value: {
    width: "100%",
    marginRight: 5,

    fontSize: 14,
    color: "#fff",
  },
});
