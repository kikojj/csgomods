import { makeStyles } from "@material-ui/styles";

export type Props = {
  marginTop?: number;
}
export const useStyles = makeStyles({
  container: {
    marginTop: ({ marginTop }: Props) => marginTop
  },
});
