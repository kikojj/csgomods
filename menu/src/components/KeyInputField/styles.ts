import { makeStyles } from "@material-ui/styles";

export type Props = {
  marginTop?: number;
}
export const useStyles = makeStyles({
  container: {
    marginTop: ({ marginTop }: Props) => marginTop,
    width: "100%",
  },
  helperText: {
    marginTop: 4,
    paddingLeft: 10,
    fontWeight: 400,
    fontSize: 12,
    color: "rgba(255,255,255,0.6)",
  },
});
