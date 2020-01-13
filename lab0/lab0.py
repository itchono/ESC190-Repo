from lab0_utilities import *
	
class Languages:
	def __init__(self):
		self.data_by_year = {}

	def build_trees_from_file(self, file_object):
		# implement
		pass


	def query_by_name(self, language_name):
		# implement
		pass
				

	def query_by_count(self, threshold = 0):
		# implement
		pass



class BalancingTree:
	def __init__(self, root_node):
		self.root = root_node
	
	def balanced_insert(self, node, curr = None):
		curr = curr if curr else self.root
		self.insert(node, curr)
		self.balance_tree(node)


	def insert(self, node, curr = None):
		curr = curr if curr else self.root
		# insert at correct location in BST
		if node._val < curr._val:
			if curr.left is not None:
				self.insert(node, curr.left)
			else:
				node.parent = curr
				curr.left = node
		else:
			if curr.right is not None:
				self.insert(node, curr.right)
			else:
				node.parent = curr
				curr.right = node
		return


	def balance_tree(self, node):
		# implement
		pass
 

	def update_height(self, node):
		node.height = 1 + max(self.height(node.left), self.height(node.right))


	def height(self, node):
		return node.height if node else -1


	def left_rotate(self, z):
		y = z.right
		y.parent = z.parent
		if y.parent is None:
			self.root = y
		else:
			if y.parent.left is z:
				y.parent.left = y
			elif y.parent.right is z:
				y.parent.right = y
		z.right = y.left
		if z.right is not None:
			z.right.parent = z
		y.left = z
		z.parent = y
		self.update_height(z)
		self.update_height(y)


	def right_rotate(self, z):
		# implement
		pass
		# use left_rotate as a reference


	def find_balance_factor(self, node):
		# implement
		pass


	def is_balanced(self):
		#implement
		pass
