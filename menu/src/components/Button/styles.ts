import { makeStyles } from "@material-ui/styles";

export type Props = {
  color: string;
  marginTop?: number;
  marginRight?: number;
};
export const useStyles = makeStyles({
  container: {
    marginTop: ({ marginTop }: Props) => marginTop,
    marginRight: ({ marginRight }: Props) => marginRight,
    padding: "7px 15px",

    display: "flex",
    alignItems: "center",
    justifyContent: "center",

    borderRadius: 2,
    backgroundColor: (props: Props) => props.color,

    color: "#fff",
    fontSize: 14,

    cursor: "pointer",
  },
});
