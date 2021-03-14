import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export type Props = {
  value: number;
  type: "int" | "float";
  color: string;
};
export const useStyles = makeStyles({
  container: {
    padding: (props: Props) => (props.type === "int" ? "4px 8px" : ""),
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
  trackBackground: {
    height: 8,
    display: "flex",
    width: "100%",
  },
  trackValue: {
    height: 8,
    width: "100%",
    borderRadius: 4,
    background: (props: Props) =>
      `linear-gradient(90deg, ${hexAlpha(props.color, 50)} 0%, ${props.color} ${props.value}%, ${colors.gray} ${
        props.value
      }%, ${colors.gray} 100%)`,
    alignSelf: "center",
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
