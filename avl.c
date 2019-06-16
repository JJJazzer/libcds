/*
 * file name: avl.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Sun 16 Jun 2019 01:58:29 PM CST
 */

static locate single_rotateleft(position k2)
{
	position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
}

static locate double_rotateleft(position k3)
{
	k3->left = single_rotate_right(k3->left);
	return single_rotate_left(k3);
}
