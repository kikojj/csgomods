import { makeStyles } from "@material-ui/styles";

export type Props = {
  type: "int" | "float";
};
export const useStyles = makeStyles({
  container: {
    padding: ({ type }: Props) => (type === "int" ? "4px 8px" : ""),
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
    width: "100%",
  },
  content: {
    display: "flex",
    justifyContent: "center",
    flexWrap: "wrap",
    width: "100%",
  },
  valueMark: {
    height: 16,
    width: 16,
    borderRadius: 10,
    backgroundColor: "#FFF",
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
  },
  btn_minus: {
    marginRight: 15,
    marginBottom: 6,

    display: "block",
    backgroundColor: "transparent",

    color: "#fff",
    fontSize: 36,
    lineHeight: "5px",

    cursor: "pointer",
  },
  btn_plus: {
    marginLeft: 15,
    marginBottom: 2,

    display: "block",
    backgroundColor: "transparent",

    color: "#fff",
    fontSize: 24,
    lineHeight: "16px",

    cursor: "pointer",
  },
});
